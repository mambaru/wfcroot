#pragma once

#include <string>
#include <fas/typemanip/empty_type.hpp>

namespace wfc
{

template<
  typename Req = fas::empty_type,
  typename Res = fas::empty_type,
  typename Opt = fas::empty_type
>
struct tank_options: Opt
{
  typedef Opt user_options;
  typedef Req request_type;
  typedef Res response_type;

  std::string target;
  request_type request;
  response_type response;

  size_t gunfire_size = 30; // количество непрерывных запросов - "очередь"
  size_t gunfire_count = 4; // Число "очередей" размером gunfire_size и завершение работы
  time_t gunfire_mks = 1000000; // Интервал между "очередями"
  size_t gunfire_max_waits = 1000; // Мак. число запросов ожидающих ответа для след. очереди 
  time_t statistics_log_ms = 1000;

  bool use_api_schema = true;
};


struct stat_tank_options
{
  
};

}
