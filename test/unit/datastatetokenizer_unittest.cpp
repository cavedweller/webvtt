#include "cuetexttokenizer_fixture"

class DataStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void DataTokenize( const char *text ) {
      state = DATA;
      pos = reinterpret_cast<const webvtt_byte *>( text );
      status = webvtt_data_state( &pos, &state, &res );
    }
};

/*
 * Tests if the data state tokenizer will parse basic text.
 */
TEST_F(DataStateTokenizerTest, BasicText)
{
  DataTokenize( "Some Text Here" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "Some Text Here", ParsedText() );
}

/*
 * Tests if the data state tokenizer will switch to the escape state if it
 * encounters an '&' character.
 */
TEST_F(DataStateTokenizerTest, EscapeStateChange)
{
  DataTokenize( "&amp" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'a', GetCurrentChar() );
  EXPECT_EQ( ESCAPE, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the data state tokenizer returns WEBVTT_SUCCESS if it reaches a '<'
 * character after it has parsed some text.
 */
TEST_F(DataStateTokenizerTest, LTFinishedToken)
{
  DataTokenize( "Text <b>" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '<', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "Text ", ParsedText() );
}

/*
 * Tests if the data state tokenizer switches to the tag state if it encounters
 * an '<' character and it hasn't parsed any text yet.
 */
TEST_F(DataStateTokenizerTest, LTStartedToken)
{
  DataTokenize( "<b>" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'b', GetCurrentChar() );
  EXPECT_EQ( TAG, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the data state tokenizer returns WEBVTT_SUCCESS upon reaching the
 * '\0' character.
 */
TEST_F(DataStateTokenizerTest, NullByteFinishedToken)
{
  DataTokenize( "Text \0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "Text ", ParsedText() );
}