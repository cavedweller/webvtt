#include "cuetexttokenizer_fixture"

class TimeStampStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void TimeStampTokenize( const char *text ) {
      state = TIME_STAMP_TAG;
      pos = text;
      status = webvtt_timestamp_state( &pos, &state, &res );
    }
};

/*
 * Tests if the time stamp state tokenizer parses simple text.
 */
TEST_F(TimeStampStateTokenizerTest, BasicText)
{
  TimeStampTokenize( "11:00.000" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( TIME_STAMP_TAG, GetState() );
  EXPECT_STREQ( "11:00.000", ParsedText() );
}

/*
 * Tests if the time stamp state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(TimeStampStateTokenizerTest, GTFinished)
{
  TimeStampTokenize( "11:00.000>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( TIME_STAMP_TAG, GetState() );
  EXPECT_STREQ( "11:00.000", ParsedText() );
}

/*
 * Tests if the time stamp state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(TimeStampStateTokenizerTest, NullByteFinished)
{
  TimeStampTokenize( "11:00.000\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( TIME_STAMP_TAG, GetState() );
  EXPECT_STREQ( "11:00.000", ParsedText() );
}
