#pragma once
#include <wonderwaffel/waffel_domain.hpp>
#include <wonderwaffel/tank_options.hpp>
#include <wonderwaffel/igun.hpp>
#include <wonderwaffel/logger.hpp>
#include <wflow/wflow.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <iostream>

namespace wfc
{

template<typename Name, typename I, typename Opt = tank_options<> >
class tank_domain
  : public waffel_domain<Opt, stat_tank_options>
  , public std::enable_shared_from_this< tank_domain<Name, I, Opt> >
{
  typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point_t;
  
  struct bang_stat
  {
    size_t wait_counter = 0;
    size_t request_counter = 0;
    size_t response_counter = 0;
    size_t bad_counter = 0;
    time_point_t start_time;
    time_point_t finish_time;
    
    size_t get_interval() const
    {
      return static_cast<size_t>( std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time).count() );
    }

    size_t get_rate() const
    {
      return response_counter * 1000000 / this->get_interval();
    }

  };

public:
  typedef std::mutex mutex_type;
  typedef tank_domain<Name, I, Opt> self;
  typedef igun<I, Opt> gun_interface;
  typedef waffel_domain<Opt, stat_tank_options> super;
  typedef typename super::options_type options_type;
  typedef typename super::timer_id_t timer_id_t;

  virtual void start() override
  {
    _gun =  this->template get_object<gun_interface>("wonderwaffel", Name()() );
    _options = this->options();
    _target = this->template get_target<I>(_options.target);
    _gun->initialize(_target, _options);
    _gunfire_counter = _options.gunfire_count;
    
    if (auto pstat = this->get_statistics() )
      _meter = pstat->create_time_meter("time");
    
    this->get_workflow()->safe_post( std::chrono::seconds(2), std::bind(&self::create_timer, this) );
    /*if ( this->get_statistics() == nullptr )
      abort();*/
  }

  void create_timer()
  {
    _bang_stat = bang_stat();
    DOMAIN_LOG_BEGIN("---------------START--------------------")
    _bang_stat.start_time = std::chrono::high_resolution_clock::now();
    this->get_workflow()->create_timer(std::chrono::microseconds(_options.gunfire_mks), std::bind(&self::gunfire, this) );
    this->get_workflow()->create_timer(std::chrono::milliseconds(_options.statistics_log_ms), std::bind(&self::show_stat, this) );
    this->global()->after_stop.insert(std::bind(&self::show_stat, this));
  }

  bool gunfire()
  {
    std::lock_guard<mutex_type> lk(_mutex);
    if ( this->global_stop_flag() )
      return false;
    
    if ( _gunfire_counter == 0 && _bang_stat.wait_counter == 0)
    {
      DOMAIN_LOG_END("---------------FINISH--------------------")
      wfc_exit();
      return false;
    }

    if ( _gunfire_counter != 0 && _bang_stat.wait_counter < _options.gunfire_max_waits)
    {
      --_gunfire_counter;
      for (size_t i = 0; i < _options.gunfire_size; ++i)
      {
        ++_bang_stat.wait_counter;
        ++_bang_stat.request_counter;
        auto tp = _meter.create_shared(1u);
        _gun->bang([this, tp](bool status)
        {
          std::lock_guard<mutex_type> lk2(_mutex);
          if ( this->global_stop_flag() )
            return;
          --_bang_stat.wait_counter;
          ++_bang_stat.response_counter;
          if ( !status) ++_bang_stat.bad_counter;
          if ( !status || _bang_stat.wait_counter==0)
          {
            auto finish = std::chrono::high_resolution_clock::now();
            auto interal = std::chrono::duration_cast<std::chrono::microseconds>(finish - _bang_stat.start_time).count();
            auto rate = static_cast<long>(_bang_stat.response_counter * 1000000) / interal;
            DOMAIN_LOG_END("---------------FINISH2-------------------- " << status << ":" << _bang_stat.wait_counter << ":" << _bang_stat.request_counter << ":" << _bang_stat.response_counter )
            DOMAIN_LOG_MESSAGE("RATE: " << rate)
            wfc_exit();
          }
        });
      }
    }
    return !this->global_stop_flag() && _gunfire_counter!=0;
  }
  
  bool show_stat()
  {
    bang_stat cur_stat;
    cur_stat = this->start_stat();
    TANK_LOG_MESSAGE(this->name() << " statistics")
    TANK_LOG_MESSAGE("\tTIME: " << cur_stat.get_interval() << " mks")
    TANK_LOG_MESSAGE("\tRATE: " << cur_stat.get_rate() << " persec")
    TANK_LOG_MESSAGE("\tCOUNT: " << cur_stat.response_counter)
    TANK_LOG_MESSAGE("\tWAIT: " << long(cur_stat.wait_counter) )
    TANK_LOG_MESSAGE("\tBAD: " << cur_stat.bad_counter)
    
    return true;
  }
  
  bang_stat start_stat()
  {
    std::lock_guard<mutex_type> lk(_mutex);
    bang_stat res = std::move(_bang_stat);
    _bang_stat = bang_stat();
    res.finish_time = std::chrono::high_resolution_clock::now();
    _bang_stat.wait_counter = res.wait_counter;
    _bang_stat.start_time = std::chrono::high_resolution_clock::now();
    return res;
  }
  
private:
  std::shared_ptr<gun_interface> _gun;
  std::shared_ptr<I> _target;
  options_type _options;
  timer_id_t _timer = -1;
  size_t _gunfire_counter = 0;
  bang_stat _bang_stat;
  mutex_type _mutex;
  time_meter _meter;
};

}
