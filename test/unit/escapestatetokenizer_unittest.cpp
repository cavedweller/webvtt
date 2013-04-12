#include "cuetexttokenizer_fixture"

class EscapeStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void EscapeTokenize( const char *text ) {
      state = ESCAPE;
      pos = reinterpret_cast<const webvtt_byte *>( text );
      status = webvtt_escape_state( &pos, &state, &res );
    }
};

/*
 * Please note that based on the algorithm the escape state tokenizer assumes
 * that an '&' character should be at the front of the string passed in and
 * automatically appends one to it.
 */

/*
 * Tests if the escape state tokenizer exits correctly upon receiving a null
 * byte character.
 */
TEST_F(EscapeStateTokenizerTest, NullByteFinished)
{
  EscapeTokenize( "Text\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( ESCAPE, GetState() );
  EXPECT_STREQ( "&Text", ParsedText() );
}

/*
 * Tests if the escape state tokenizer exits correctly upon receiving an
 * '<' character.
 */
TEST_F(EscapeStateTokenizerTest, LTFinished)
{
  EscapeTokenize( "Text<c>" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '<', GetCurrentChar() );
  EXPECT_EQ( ESCAPE, GetState() );
  EXPECT_STREQ( "&Text", ParsedText() );
}

/*
 * Tests if the escape state tokenizer exist correctly upon encountering non
 * alpha numeric characters.
 */
TEST_F(EscapeStateTokenizerTest, NonAlphaNumeric)
{
  EscapeTokenize( "Text <c>" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( '<', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "&Text ", ParsedText() );
}

/*
 * Tests if the escape state tokenizer exist correctly upon encountering a
 * string that is not a valid escape sequence.
 */
TEST_F(EscapeStateTokenizerTest, IncorrectEscape)
{
  EscapeTokenize( "amb; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "&amb;", ParsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct ampersand escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectAmpersand)
{
  EscapeTokenize( "amp; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "&", ParsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct greater than escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectLT)
{
  EscapeTokenize( "lt; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "<", ParsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct less than escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectGT)
{
  EscapeTokenize( "gt; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( ">", ParsedText() );
}

/*
 * Tests if the escape state tokenizer parses an extra ampersand correctly.
 */
TEST_F(EscapeStateTokenizerTest, ExtraAmpersand)
{
  EscapeTokenize( "am&amp; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( DATA, GetState() );
  EXPECT_STREQ( "&am&", ParsedText() );
}