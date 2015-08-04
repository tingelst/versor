#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

TEST_CASE("Initial test")
{
  REQUIRE(1.0 == 1.0);
}
