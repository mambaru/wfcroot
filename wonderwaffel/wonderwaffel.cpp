#include <wfc/name.hpp>
#include <wonderwaffel/wonderwaffel.hpp>
#include "wonderwaffel_build_info.h"
#include <wfc/tank/logger.hpp>
#include <wjrpc/outgoing/outgoing_request.hpp>
#include <wjrpc/outgoing/outgoing_request_json.hpp>
#include <atomic>

namespace {

struct tank_io_options_base
{
  bool show_request = false;
  bool show_response = false;
  bool check_response = false;
  // Если указан, то request/response это parans и result в запросе, id генерится автоматически
  std::shared_ptr<std::string> jsonrpc_method = nullptr;
};

struct tank_io_options
{
  tank_io_options_base io;
};

struct tank_io_options_json
{
  JSON_NAME(show_request)
  JSON_NAME(show_response)
  JSON_NAME(check_response)
  JSON_NAME(jsonrpc_method)

  typedef wjson::object<
    tank_io_options_base, 
    wjson::member_list<
      wjson::member<n_show_request, tank_io_options_base, bool, &tank_io_options_base::show_request>,
      wjson::member<n_show_response, tank_io_options_base, bool, &tank_io_options_base::show_response>,
      wjson::member<n_check_response, tank_io_options_base, bool, &tank_io_options_base::check_response>,
      wjson::member<n_jsonrpc_method, tank_io_options_base, std::shared_ptr<std::string>, 
                    &tank_io_options_base::jsonrpc_method, 
                    wjson::pointer<std::shared_ptr<std::string>, wjson::value<std::string> > >
    >
  > base_json_type;
  
  JSON_NAME(io)
  typedef wjson::object<
    tank_io_options, 
    wjson::member_list<
      wjson::member<n_io, tank_io_options, tank_io_options_base, 
                    &tank_io_options::io, base_json_type>
    >
  > type;
  
  typedef type::target target;
  typedef type::serializer serializer;
  typedef type::member_list member_list;
};

int make_request_id()
{
  static std::atomic_int count(0);
  return ++count;
}
bool make_request(const tank_io_options& opt, wfc::iinterface::data_type& d, wfc::iinterface::data_type& )
{
  if ( opt.io.jsonrpc_method != nullptr && !opt.io.jsonrpc_method->empty() )
  {
    typedef wfc::iinterface::data_type data_type;
    typedef wjrpc::outgoing_request<data_type> jrpc_request_t;
    typedef wjrpc::outgoing_request_json<wjson::raw_value<data_type> > jrpc_request_json;
    jrpc_request_t req;
    req.method = *opt.io.jsonrpc_method;
    req.params = std::make_unique<data_type>( std::move(d) );
    req.id = make_request_id();
    
    jrpc_request_json::serializer()( req, std::back_inserter(d) );
  }
  
  if (opt.io.show_request)
  {
    TANK_LOG_MESSAGE("IO request [" << std::string(d.begin(), d.end()) << "]")
  }
  return true;
}

bool check_response(const tank_io_options& opt, const wfc::iinterface::data_type&, const wfc::iinterface::data_type&, const wfc::iinterface::data_type& d)
{
  if (opt.io.show_response)
  {
    TANK_LOG_MESSAGE("IO response [" << std::string(d.begin(), d.end()) << "]")
  }
  return true;
}


WFC_NAME2(wonderwaffel, "wonderwaffel")

}

int main(int argc, char* argv[])
{
  // DEBUG TODO: сделать функцию enable_tank_io
  wfc::wonderwaffel<wonderwaffel_build_info> ww;
  ww.add_tank_io<wonderwaffel, tank_io_options_json>(make_request, check_response);
  ww.run(argc, argv, "Universal wonderwaffel for high load testing");
}
