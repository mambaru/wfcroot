#pragma once

#include <wfc/domain_object.hpp>
#include <wfc/iinterface.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace wfc{

template<typename O = fas::empty_type, typename StatOpt = nostat>
class waffel_domain
  : public domain_object<iinterface, O, StatOpt>
{
};


}
