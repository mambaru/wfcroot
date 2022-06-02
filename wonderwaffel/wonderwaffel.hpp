#pragma once

#include <wfc/wfc.hpp>
#include <wfcroot/wfcroot.hpp>
#include <wfc/module/ipackage.hpp>
#include <wfc/core/build_info.hpp>
#include <wonderwaffel/tank_package.hpp>
#include <wonderwaffel/waffel_package.hpp>
#include <memory>
#include <list>

namespace wfc{

template<typename BuildInfo = empty_build_info >
class wonderwaffel
{
  template<typename N, typename ReqJson, typename ResJson, typename OptJson, typename I>
  struct tank_helper
  {
    typedef tank_package<N, I, tank_config_json<ReqJson, ResJson, OptJson>, build_info_t<N, BuildInfo> > package_type;
    typedef typename package_type::request_type request_type;
    typedef typename package_type::response_type response_type;
    typedef typename package_type::request_ptr request_ptr;
    typedef typename package_type::response_ptr response_ptr;
    typedef typename package_type::target_method target_method;

    typedef typename package_type::request_generator request_generator;
    typedef typename package_type::response_checker response_checker;
  };

  template<typename N, typename ReqJson, typename ResJson,  typename I>
  struct tank_helper1: tank_helper<N, ReqJson, ResJson, wjson::empty_object<>, I >
  {};

  template<typename N, typename Req, typename Res, typename I>
  struct tank_helper2: tank_helper<N, wjson::empty_object<Req>, wjson::empty_object<Res>, wjson::empty_object<>, I>
  {
  };

  template<typename N >
  struct tank_helper3: tank_helper<
    N, wjson::raw_value<iinterface::data_type>, 
    wjson::raw_value<iinterface::data_type>, 
    wjson::empty_object<>, iinterface >
  {};

  template<typename N, typename OptJ >
  struct tank_helper4: tank_helper<
    N, wjson::raw_value<iinterface::data_type>, 
    wjson::raw_value<iinterface::data_type>, 
    OptJ, iinterface >
  {};

public:
  template<typename T>
  void add_package()
  {
    _packages.push_back( std::make_shared<T>() );
  }

  template<typename N, typename T>
  void add_object()
  {
    typedef waffel_package< build_info_t<N, BuildInfo>, N, T> package_type;
    _packages.push_back( std::make_shared<package_type>() );
  }

  template<typename N, typename ReqJ, typename ResJ, typename OptJ, typename I>
  void add_tank(
    void (I::* mem_ptr)(std::unique_ptr<typename ReqJ::target>, std::function< void(std::unique_ptr<typename ResJ::target>) >),
    typename tank_helper<N, ReqJ, ResJ, OptJ, I>::request_generator rg = nullptr,
    typename tank_helper<N, ReqJ, ResJ, OptJ, I>::response_checker rc = nullptr
  )
  {
    auto ptank = std::make_shared< typename tank_helper<N, ReqJ, ResJ, OptJ, I>::package_type >(mem_ptr, rg, rc);
    _packages.push_back(ptank);
  }


  template<typename N, typename ReqJ, typename ResJ, typename I>
  void add_tank(
    void (I::* mem_ptr)(std::unique_ptr<typename ReqJ::target>, std::function< void(std::unique_ptr<typename ResJ::target>) >),
    typename tank_helper1<N, ReqJ, ResJ, I>::request_generator rg = nullptr,
    typename tank_helper1<N, ReqJ, ResJ, I>::response_checker rc = nullptr
  )
  {
    auto ptank = std::make_shared< typename tank_helper1<N, ReqJ, ResJ, I>::package_type >(mem_ptr, rg, rc);
    _packages.push_back(ptank);
  }


  template<typename N, typename Req, typename Res, typename I>
  void add_tank(
    void (I::* mem_ptr)(std::unique_ptr<Req>, std::function< void(std::unique_ptr<Res>) >),
    typename tank_helper2<N, Req, Res, I>::request_generator rg = nullptr,
    typename tank_helper2<N, Req, Res, I>::response_checker rc = nullptr
  )
  {
    auto ptank = std::make_shared< typename tank_helper2<N, Req, Res, I>::package_type >(mem_ptr, rg, rc);
    _packages.push_back(ptank);
  }

  template<typename N>
  void add_tank_io(
    typename tank_helper3<N>::request_generator rg = nullptr,
    typename tank_helper3<N>::response_checker rc = nullptr )
  {
  
    auto ptank = std::make_shared< typename tank_helper3<N>::package_type >(&iinterface::perform_io, rg, rc);
    _packages.push_back(ptank);
  }

  template<typename N, typename OptJ >
  void add_tank_io(
    typename tank_helper4<N, OptJ>::request_generator rg = nullptr,
    typename tank_helper4<N, OptJ>::response_checker rc = nullptr )
  {
    auto ptank = std::make_shared< typename tank_helper4<N, OptJ>::package_type >(&iinterface::perform_io, rg, rc);
    _packages.push_back(ptank);
  }

  int run(int argc, char* argv[], std::string helpstring = std::string() )
  {
    return wfc<BuildInfo>(wfcroot(_packages)).run(argc, argv, helpstring);
  }

  template<typename Req>
  static bool request_gen_def(Req*)
  {
    return true;
  }

  template<typename Res>
  static bool response_check_def(Res*)
  {
    return true;
  }
private:
  std::list< std::shared_ptr<ipackage> > _packages;
};

}
