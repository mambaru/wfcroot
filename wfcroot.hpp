#pragma once

#include <wfc/module/ipackage.hpp>
#include <memory>
#include <list>

namespace wfc{ 
  
/*typedef std::shared_ptr<ipackage> package_ptr;
  typedef std::initializer_list< package_ptr > packages_initializer;
*/

std::list< std::shared_ptr<ipackage> >
wfcroot( std::list< std::shared_ptr<ipackage> > packages);

}
