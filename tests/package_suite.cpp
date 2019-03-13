#include <fas/testing.hpp>

namespace {

UNIT(init, "")
{
  using namespace fas::testing;
  t << nothing;
}

}
  
BEGIN_SUITE(package_suite, "")
  ADD_UNIT( init )
END_SUITE(package_suite)
