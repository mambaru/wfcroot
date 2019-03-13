#pragma once

#include <wfc/module/ipackage.hpp>
#include <memory>
#include <list>

namespace wfc{ 
  
/**
 * \defgroup wfcroot Стандартные пакеты WFC
 */
  
std::list< std::shared_ptr<ipackage> >
wfcroot( std::list< std::shared_ptr<ipackage> > packages);

}
