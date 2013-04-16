#include "cuetexttokenizer_fixture"

class AnnotationStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void AnnotationTagTokenize( const char *text ) {
      state = START_TAG_ANNOTATION;
      pos = reinterpret_cast<const webvtt_byte *>( text );
      status = webvtt_annotation_state( &pos, &state, &res );
    }
};

/*
 * Tests if the annotation state tokenizer parses simple text.
 */
TEST_F(AnnotationStateTokenizerTest, BasicText)
{
  AnnotationTagTokenize( "Annotation" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "Annotation", ParsedText() );
}

/*
 * Tests if the annotation state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(AnnotationStateTokenizerTest, GTFinished)
{
  AnnotationTagTokenize( "Annotation>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "Annotation", ParsedText() );
}

/*
 * Tests if the annotation state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(AnnotationStateTokenizerTest, NullByteFinished)
{
  AnnotationTagTokenize( "Annotation\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_STREQ( "Annotation", ParsedText() );
}
