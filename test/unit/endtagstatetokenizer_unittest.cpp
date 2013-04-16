#include "cuetexttokenizer_fixture"

class EndTagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void EndTagTokenize( const char *text ) {
      state = END_TAG;
      pos = text;
      status = webvtt_end_tag_state( &pos, &state, &res );
    }
};

/*
 * Tests if the end tag state tokenizer parses simple text.
 */
TEST_F(EndTagStateTokenizerTest, BasicText)
{
  EndTagTokenize( "ruby" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( END_TAG, GetState() );
  EXPECT_STREQ( "ruby", ParsedText() );
}

/*
 * Tests if the end tag state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(EndTagStateTokenizerTest, GTFinished)
{
  EndTagTokenize( "ruby>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( END_TAG, GetState() );
  EXPECT_STREQ( "ruby", ParsedText() );
}

/*
 * Tests if the end tag state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(EndTagStateTokenizerTest, NullByteFinished)
{
  EndTagTokenize( "ruby\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( END_TAG, GetState() );
  EXPECT_STREQ( "ruby", ParsedText() );
}
