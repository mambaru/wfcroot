
#include "wfcroot.hpp"

#include <package/jsonrpc_package.hpp>
#include <package/core_package.hpp>
#include <package/io_package.hpp>
#include <wfc/module/ipackage.hpp>

#include <algorithm>
#include <iostream>

namespace wfc{ 

std::list< std::shared_ptr<ipackage> >
  wfcroot( std::list< std::shared_ptr<ipackage> > packages)
{
  std::list< std::shared_ptr<ipackage> > defpack =
  {
    std::make_shared<core_package>(),
    std::make_shared<io_package>(),
    std::make_shared<jsonrpc_package>()
  };
  
  for (auto p : packages )
  {
    auto end = std::remove_if( defpack.begin(),  defpack.end(), [p](std::shared_ptr<ipackage> dp) 
    {
      return dp->name() == p->name();
    });
    defpack.erase(end, defpack.end() );
  }
  std::copy(packages.begin(), packages.end(), std::back_inserter(defpack));
  return defpack;
}

}
