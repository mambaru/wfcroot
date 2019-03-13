#include <fas/testing.hpp>
#include <wfcroot/wfcroot.hpp>

namespace {

UNIT(unit1, "")
{
  using namespace fas::testing;
  auto list = wfc::wfcroot({});
  t << equal<expect, size_t>(list.size(), 3) << FAS_FL;
}

}
  
BEGIN_SUITE(package_suite, "")
  ADD_UNIT( unit1 )
END_SUITE(package_suite)
