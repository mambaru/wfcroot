#pragma once

#include <wfc/module/ipackage.hpp>
#include <memory>
#include <list>

namespace wfc{ 
  
std::list< std::shared_ptr<ipackage> >
wfcroot( std::list< std::shared_ptr<ipackage> > packages);

}
