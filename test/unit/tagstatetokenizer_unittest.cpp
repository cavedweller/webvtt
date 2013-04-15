#include "cuetexttokenizer_fixture"

class TagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void TagTokenize( const char *text ) {
      state = TAG;
      pos = reinterpret_cast<const webvtt_byte *>( text );
      status = webvtt_tag_state( &pos, &state, &res );
    }
};

/*
 * Tests if the tag state tokenizer switches to start tag class state correctly
 * when receiving a '.' character.
 */
TEST_F(TagStateTokenizerTest, StartTagClassStateChange)
{
  TagTokenize( ".class" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'c', GetCurrentChar() );
  EXPECT_EQ( START_TAG_CLASS, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to start tag state correctly
 * when receiving a character that isn't handled by the other states character.
 */
TEST_F(TagStateTokenizerTest, StartTagStateChange)
{
  TagTokenize( "ruby" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'u', GetCurrentChar() );
  EXPECT_EQ( START_TAG, GetState() );
  EXPECT_STREQ( "r", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to end state correctly when
 * receiving a '/' character.
 */
TEST_F(TagStateTokenizerTest, EndTagStateChange)
{
  TagTokenize( "/b" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'b', GetCurrentChar() );
  EXPECT_EQ( END_TAG, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to time stamp tag state correctly
 * when receiving a ASCII digit.
 */
TEST_F(TagStateTokenizerTest, TimeStampStateChange)
{
  TagTokenize( "12" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( '2', GetCurrentChar() );
  EXPECT_EQ( TIME_STAMP_TAG, GetState() );
  EXPECT_STREQ( "1", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a ' ' character.
 */
TEST_F(TagStateTokenizerTest, SpaceAnnotationStateChange)
{
  TagTokenize( " Annotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\n' character.
 */
TEST_F(TagStateTokenizerTest, NewLineAnnotationStateChange)
{
  TagTokenize( "\nAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\r' character.
 */
TEST_F(TagStateTokenizerTest, CRAnnotationStateChange)
{
  TagTokenize( "\rAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\f' character.
 */
TEST_F(TagStateTokenizerTest, FormFeedAnnotationStateChange)
{
  TagTokenize( "\fAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\t' character.
 */
TEST_F(TagStateTokenizerTest, TabAnnotationStateChange)
{
  TagTokenize( "\tAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, GetStatus() );
  EXPECT_EQ( 'A', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer exits correctly when it receives a '>'
 * character.
 */
TEST_F(TagStateTokenizerTest, GTFinished)
{
  TagTokenize( ">" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( TAG, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}

/*
 * Tests if the tag state tokenizer exits correctly when it receives a '\0'
 * character.
 */
TEST_F(TagStateTokenizerTest, NullByteFinished)
{
  TagTokenize( "\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( TAG, GetState() );
  EXPECT_STREQ( "", ParsedText() );
}