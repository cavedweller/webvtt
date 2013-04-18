#include "regression_testfixture"

// TODO: introduce timeout feature to fail tests that take too long.

// Bug853879 - Infinite loop in function parse_cueparams()
// (https://bugzilla.mozilla.org/show_bug.cgi?id=853879)
//
// File contains syntax errors, but should parse successfully due to not
// aborting on errors.
TEST_F(RegressionTest,Bug853879)
{
  EXPECT_TRUE( parse( "853879-1.vtt" ) );
}

// Bug853589 - Crash [@parse_cueparams]
// (https://bugzilla.mozilla.org/show_bug.cgi?id=853589)
//
// File contains syntax errors (bad end timestamp), but should parse
// successfully due to not aborting on errors.
TEST_F(RegressionTest,Bug853589)
{
  EXPECT_TRUE( parse( "853589-1.vtt" ) );
}
