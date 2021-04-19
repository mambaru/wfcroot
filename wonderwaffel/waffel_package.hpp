#pragma once

#include <wjson/predef.hpp>
#include <wfc/module/module_list.hpp>
#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/module/component_list.hpp>
#include <wfc/core/build_info.hpp>

namespace wfc
{

template<
  typename BuildInfo, /*= build_info_t<Name, empty_build_info>*/
  typename Name,
  typename DomainObject,
  typename J = wjson::empty_object<typename DomainObject::options_type>,
  typename SJ = wjson::empty_object<nostat>
>
class waffel_package: public module_list<
              BuildInfo,
              component_list<
                Name,
                multiton<
                  Name,
                  instance< DomainObject >,
                  J,
                  component_features::Defaults,
                  SJ
                >
              >
            >
{
};

}
