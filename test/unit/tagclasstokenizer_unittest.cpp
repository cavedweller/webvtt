#include "cuetexttokenizer_fixture"
#include <webvttxx/string>
extern "C" {
  #include "libwebvtt/string.c"
}

class ClassStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    virtual void SetUp() {
      CueTextTokenizerTest::SetUp();
      webvtt_create_stringlist( &classes );
    }
    
    virtual void TearDown() {
      CueTextTokenizerTest::TearDown();
      webvtt_release_stringlist( &classes );
    }
    
    WebVTT::StringList ParsedClasses() {
      return WebVTT::StringList( classes );
    }
    
    void StartTagTokenize( const char *text ) {
      state = START_TAG_CLASS;
      pos = text;
      status = webvtt_class_state( &pos, &state, classes );
    }
    
  private:
    webvtt_stringlist *classes;
};

/*
 * Tests if the class state tokenizer parses multiple classes correctly.
 */
TEST_F(ClassStateTokenizerTest, ClassParsing)
{
  StartTagTokenize( "class.subclass.subsub>" );
  
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( START_TAG_CLASS, GetState() );
  EXPECT_STREQ( "class", ParsedClasses()[0].utf8() );
  EXPECT_STREQ( "subclass", ParsedClasses()[1].utf8() );
  EXPECT_STREQ( "subsub", ParsedClasses()[2].utf8() );
}

/*
 * Tests if the class state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(ClassStateTokenizerTest, GTFinished)
{
  StartTagTokenize( "class>Text" );
  
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '>', GetCurrentChar() );
  EXPECT_EQ( START_TAG_CLASS, GetState() );
  EXPECT_STREQ( "class", ParsedClasses()[0].utf8() );
}

/*
 * Tests if the class state state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(ClassStateTokenizerTest, NullByteFinished)
{
  StartTagTokenize( "class\0" );
  
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\0', GetCurrentChar() );
  EXPECT_EQ( START_TAG_CLASS, GetState() );
  EXPECT_STREQ( "class", ParsedClasses()[0].utf8() );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\n' character.
 */
TEST_F(ClassStateTokenizerTest, SpaceAnnotationStateChange)
{
  StartTagTokenize( " class" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( ' ', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_EQ( ParsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\n' character.
 */
TEST_F(ClassStateTokenizerTest, NewLineAnnotationStateChange)
{
  StartTagTokenize( "\nclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\n', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_EQ( ParsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\r' character.
 */
TEST_F(ClassStateTokenizerTest, CRAnnotationStateChange)
{
  StartTagTokenize( "\rclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\r', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_EQ( ParsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\f' character.
 */
TEST_F(ClassStateTokenizerTest, FormFeedAnnotationStateChange)
{
  StartTagTokenize( "\fclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\f', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_EQ( ParsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\t' character.
 */
TEST_F(ClassStateTokenizerTest, TabAnnotationStateChange)
{
  StartTagTokenize( "\tclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, GetStatus() );
  EXPECT_EQ( '\t', GetCurrentChar() );
  EXPECT_EQ( START_TAG_ANNOTATION, GetState() );
  EXPECT_EQ( ParsedClasses().length(), 0 );
}
