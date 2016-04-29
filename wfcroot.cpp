#include "wfc_jsonrpc/jsonrpc/jsonrpc_package.hpp"
#include "wfc_io/package/io_package.hpp"
#include "wfc_logger/package/logger_package.hpp"
#include "wfc_core/package/core_package.hpp"
#include "wfc_config/package/config_package.hpp"
#include "wfc_startup/package/startup_package.hpp"
#include "wfcroot.hpp"
#include <algorithm>
#include <iostream>

namespace wfc{ 

namespace 
{
  inline bool wfcroot_less(std::shared_ptr<ipackage> left, std::shared_ptr<ipackage> right)
  {
    return left->name() < right->name();
  }

  inline bool wfcroot_equal(std::shared_ptr<ipackage> left, std::shared_ptr<ipackage> right)
  {
    return left->name() == right->name();
  }
}

std::list< std::shared_ptr<ipackage> >
wfcroot( std::list< std::shared_ptr<ipackage> > packages)
{
  packages.sort(wfcroot_less);

  std::list< std::shared_ptr<ipackage> > defpack =
  {
    std::make_shared<startup_package>(),
    std::make_shared<config_package>(),
    std::make_shared<core_package>(),
    std::make_shared<logger_package>(),
    std::make_shared<io_package>(),
    std::make_shared<jsonrpc_package>()
  };

  defpack.sort(wfcroot_less);
  packages.merge(defpack, wfcroot_less);
  packages.unique(wfcroot_equal);
  return packages;
}

}
