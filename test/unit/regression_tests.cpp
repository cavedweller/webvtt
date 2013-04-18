#include "regression_testfixture"

// TODO: introduce timeout feature to fail tests that take too long.

// Infinite loop in function parse_cueparams()
//
// File contains syntax errors, but should parse successfully due to not
// aborting on errors.
TEST_F(RegressionTest,Bug853879)
{
  EXPECT_TRUE( parse( "853879-1.vtt" ) );
}

// Bug853589 - Crash [@parse_cueparams]
//
// File contains syntax errors (bad end timestamp), but should parse
// successfully due to not aborting on errors.
TEST_F(RegressionTest,Bug853589)
{
  EXPECT_TRUE( parse( "853589-1.vtt" ) );
}
