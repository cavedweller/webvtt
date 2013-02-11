#include <gtest/gtest.h>
#include <webvtt/string.h>

/**
 * an-nyung ha-se-yo encoded in UTF8
 */
const webvtt_byte UTF8AnNyungHaSeYo[] =
{
  0xEC, 0x95, 0x88, /* U+C548 */
  0xEB, 0x85, 0x95, /* U+B155 */
  0xED, 0x95, 0x98, /* U+D558 */
  0xEC, 0x84, 0xB8, /* U+C138 */
  0xEC, 0x9A, 0x94, /* U+C694 */
  0x00              /* NULL */
};

/**
 * an-nyung ha-se-yo encoded in UTF16
 */
const webvtt_uint16 UTF16AnNyungHaSeYo[] =
{
  0xC548, 0xB155, 0xD558, 0xC138, 0xC694, 0x0000
};

/**
 * Test the webvtt_utf8_length routine
 */
TEST(String,UTF8CodepointLength)
{
  ASSERT_EQ( 3, webvtt_utf8_length( UTF8AnNyungHaSeYo ) );
}

/**
 * Test the webvtt_utf8_count routine
 */
TEST(String,UTF8CodepointCount)
{
  ASSERT_EQ( 5, webvtt_utf8_count( UTF8AnNyungHaSeYo, 0 ) )
    << "Incorrectly counted UTF8 codepoints";
}

/**
 * Test the webvtt_utf8_to_utf16 routine
 */
TEST(String,UTF8ToUTF16)
{
  ASSERT_EQ( UTF16AnNyungHaSeYo[0], webvtt_utf8_to_utf16(
    UTF8AnNyungHaSeYo+0, 0, 0 ) );
  ASSERT_EQ( UTF16AnNyungHaSeYo[1], webvtt_utf8_to_utf16(
    UTF8AnNyungHaSeYo+3, 0, 0 ) );
  ASSERT_EQ( UTF16AnNyungHaSeYo[2], webvtt_utf8_to_utf16(
    UTF8AnNyungHaSeYo+6, 0, 0 ) );
  ASSERT_EQ( UTF16AnNyungHaSeYo[3], webvtt_utf8_to_utf16(
    UTF8AnNyungHaSeYo+9, 0, 0 ) );
  ASSERT_EQ( UTF16AnNyungHaSeYo[4], webvtt_utf8_to_utf16(
    UTF8AnNyungHaSeYo+12, 0, 0 ) );
}

/**
 * Test the webvtt_skip_utf8 routine
 */
TEST(String,UTF8Skip)
{
  const webvtt_byte *b = UTF8AnNyungHaSeYo + 0;
  ASSERT_TRUE( webvtt_skip_utf8( &b, 0, 4 ) != 0 ) << "Failed to skip"
    << " characters";
  ASSERT_EQ( UTF8AnNyungHaSeYo + 12, b ) << "Didn't skip to correct"
    << " position";
  ASSERT_TRUE( webvtt_skip_utf8( &b, 0, 2 ) == 0 ) << "Skipped beyond"
    << " end of string";
}

/**
 * Test the webvtt_skip_utf8 routine starting from non-header
 * character
 */
TEST(String,UTF8SkipTrailing)
{
  const webvtt_byte *b = UTF8AnNyungHaSeYo + 1;
  ASSERT_TRUE( webvtt_skip_utf8( &b, 0, 1 ) != 0 ) << "Failed to skip"
    << " character";
  ASSERT_EQ( b, UTF8AnNyungHaSeYo + 3 ) << "Skipped to incorrect"
    << " position";
}
