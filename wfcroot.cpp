#include "wfc_client/client/client_package.hpp"
#include "wfc_server/server/server_package.hpp"
#include "wfc_logger/logger/logger_package.hpp"
#include "wfc_core/core/core_package.hpp"
#include "wfc_config/config/config_package.hpp"
#include "wfc_startup/startup/startup_package.hpp"
#include "wfcroot.hpp"

namespace wfc{ 
  
std::list< std::shared_ptr<ipackage> >
wfcroot( std::list< std::shared_ptr<ipackage> > packages)
{
  packages.push_back( std::make_shared<startup_package>() );
  packages.push_back( std::make_shared<config_package>() );
  packages.push_back( std::make_shared<core_package>() );
  packages.push_back( std::make_shared<logger_package>() );
  packages.push_back( std::make_shared<server_package>() );
  packages.push_back( std::make_shared<client_package>() );
  return packages;
}

}
