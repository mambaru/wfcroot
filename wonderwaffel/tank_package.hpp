#pragma once

#include <wonderwaffel/waffel_package.hpp>
#include <wfc/tank/tank_domain.hpp>
#include <wfc/tank/tank_config_json.hpp>
#include <wfc/tank/tank_gun.hpp>

namespace wfc
{

template<typename Name, typename I, typename OptJson = tank_config_json<>, typename BuildInfo = build_info_t<Name, empty_build_info> >
class tank_package
  : public waffel_package< BuildInfo, Name, tank_domain<I, typename OptJson::target>, OptJson, stat_tank_config_json>
{

  typedef tank_domain<I, typename OptJson::target> tank_type;
  typedef waffel_package< BuildInfo, Name, tank_domain<I, typename OptJson::target>, OptJson, stat_tank_config_json > super;
public:

  typedef OptJson options_json;
  typedef typename options_json::options_json user_options_json;
  typedef typename options_json::request_json request_json;
  typedef typename options_json::response_json response_json;

  typedef typename options_json::target options_type;
  typedef typename user_options_json::target user_options_type;
  typedef typename request_json::target request_type;
  typedef typename response_json::target response_type;
  typedef std::unique_ptr<request_type> request_ptr;
  typedef std::unique_ptr<response_type> response_ptr;


  typedef tank_gun<I, options_type> tank_gun_t;
  typedef typename tank_gun_t::target_method target_method;
  typedef typename tank_gun_t::request_generator request_generator;
  typedef typename tank_gun_t::response_checker response_checker;
  typedef std::shared_ptr<tank_gun_t> tank_gun_ptr;
  typedef std::list<tank_gun_ptr> tank_list_t;

  tank_package(
    target_method tm,
    request_generator req_gen,
    response_checker res_check
  ): _tm(tm), _req_gen(req_gen), _res_check(res_check)
  {
  }

  virtual void create( std::shared_ptr<wfcglobal> g) override
  {
    if ( g != nullptr )
    {
      _owner.set_double_call_handler(std::bind(g->doublecall_handler, this->name()));
      _owner.set_no_call_handler(std::bind(g->nocall_handler, this->name()));
    }

    super::create(g);
    
    for ( auto modu : this->modules() )
    {
      for ( auto comp : modu->components() )
      {
        auto tg = std::make_shared<tank_gun_t>( _owner, _tm, _req_gen, _res_check);
        _tank_list.push_back(tg);
        g->registry.set_object("wonderwaffel", comp->name(), tg, true);
      }
    }
  }
private:
  target_method _tm;
  request_generator _req_gen;
  response_checker _res_check;
  tank_list_t _tank_list;
  wflow::owner _owner;
};


}
