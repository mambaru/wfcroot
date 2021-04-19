#pragma once

#include <wonderwaffel/waffel_package.hpp>
#include <wonderwaffel/tank_domain.hpp>
#include <wonderwaffel/tank_options_json.hpp>
#include <wonderwaffel/tank_gun.hpp>

namespace wfc
{

template<typename Name, typename I, typename OptJson = tank_options_json<>, typename BuildInfo = build_info_t<Name, empty_build_info> >
class tank_package
  : public waffel_package< BuildInfo, Name, tank_domain<Name, I, typename OptJson::target>, OptJson, stat_tank_options_json>
{

  typedef tank_domain<Name, I, typename OptJson::target> tank_type;
  typedef waffel_package< BuildInfo, Name, tank_domain<Name, I, typename OptJson::target>, OptJson, stat_tank_options_json > super;
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

  typedef void (I::* target_method)(request_ptr,std::function< void(response_ptr) >);
  typedef tank_gun<I, options_type> tank_gun_t;
  typedef typename tank_gun_t::request_generator request_generator;
  typedef typename tank_gun_t::response_checker response_checker;
  typedef std::shared_ptr<tank_gun_t> tank_gun_ptr;

  tank_package(
    target_method tm,
    request_generator req_gen,
    response_checker res_check
  ) : _tank_gun( std::make_shared<tank_gun_t>(tm, req_gen, res_check))
  {
  }

  virtual void create( std::shared_ptr<wfcglobal> g) override
  {
    super::create(g);
    g->registry.set_object("wonderwaffel", Name()(), _tank_gun, true);
  }
private:
  tank_gun_ptr _tank_gun;
};


}
