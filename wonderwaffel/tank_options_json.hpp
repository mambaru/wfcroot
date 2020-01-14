#pragma once

#include <wjson/wjson.hpp>

namespace wfc
{

template< 
  typename ReqJ = wjson::empty_object<>,
  typename ResJ = wjson::empty_object<>, 
  typename OJ = wjson::empty_object<>
>
struct tank_options_json
{
  JSON_NAME(request)
  JSON_NAME(response)
  JSON_NAME(target)
  
  JSON_NAME(gunfire_size)
  JSON_NAME(gunfire_count)
  JSON_NAME(gunfire_max_waits)
  JSON_NAME(gunfire_mks)
  JSON_NAME(statistics_log_ms)
  JSON_NAME(use_api_schema)

  
  typedef typename OJ::target base_options;
  typedef typename ReqJ::target request_options;
  typedef typename ResJ::target response_options;
  typedef tank_options<request_options, response_options, base_options> options_type;

  typedef wjson::object<
    options_type,
    wjson::member_list<
      wjson::member<n_target, options_type, std::string, &options_type::target>,
      
      wjson::member<n_gunfire_size, options_type, size_t, &options_type::gunfire_size>,
      wjson::member<n_gunfire_count, options_type, size_t, &options_type::gunfire_count>,
      wjson::member<n_gunfire_max_waits, options_type, size_t, &options_type::gunfire_max_waits>,
      wjson::member<n_gunfire_mks, options_type, time_t, &options_type::gunfire_mks, wjson::time_interval<> >,
      wjson::member<n_statistics_log_ms, options_type, time_t, &options_type::statistics_log_ms, wjson::time_interval<> >,
      wjson::member<n_use_api_schema, options_type, bool, &options_type::use_api_schema>,

      wjson::member<n_request, options_type, request_options, &options_type::request, ReqJ>,
      wjson::member<n_response, options_type, response_options, &options_type::response, ResJ>,

      wjson::base<OJ>
    >
  > type;
  typedef typename type::serializer serializer;
  typedef typename type::target target;
  typedef typename type::member_list member_list;
 
  typedef ReqJ request_json;
  typedef ResJ response_json;
  typedef OJ   options_json;
};

struct stat_tank_options_json
{
  typedef wjson::object<
    stat_tank_options,
    wjson::member_list<
    >
  > type;
  typedef typename type::serializer serializer;
  typedef typename type::target target;
  typedef typename type::member_list member_list;

};

}
