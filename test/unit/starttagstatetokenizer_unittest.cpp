#include "cuetexttokenizer_fixture"

class StartTagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void StartTagTokenize( const char *text ) {
      state = START_TAG;
      pos = reinterpret_cast<const webvtt_byte *>( text );
      status = webvtt_start_tag_state( &pos, &state, &res );
    }
};

/*
 * Tests if the start tag state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(StartTagStateTokenizerTest, GTFinished)
{
  StartTagTokenize( "ruby>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( START_TAG, GetState() );
  EXPECT_STREQ( "ruby", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to start tag class state
 * upon encountering an '.' character.
 */
TEST_F(StartTagStateTokenizerTest, StartTagClassStateChange)
{
  StartTagTokenize( "ruby.class" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'c', GetCurrentChar() );
  EXPECT_EQ( START_TAG_CLASS, GetState() );
  EXPECT_STREQ( "ruby", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\n' character.
 */
TEST_F(StartTagStateTokenizerTest, SpaceAnnotationStateChange)
{
  StartTagTokenize( " Annotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\n' character.
 */
TEST_F(StartTagStateTokenizerTest, NewLineAnnotationStateChange)
{
  StartTagTokenize( "\nAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\r' character.
 */
TEST_F(StartTagStateTokenizerTest, CRAnnotationStateChange)
{
  StartTagTokenize( "\rAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\f' character.
 */
TEST_F(StartTagStateTokenizerTest, FormFeedAnnotationStateChange)
{
  StartTagTokenize( "\fAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\t' character.
 */
TEST_F(StartTagStateTokenizerTest, TabAnnotationStateChange)
{
  StartTagTokenize( "\tAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}
