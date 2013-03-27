#include <gtest/gtest.h>
#include <string>
extern "C" {
#include <libwebvtt/lexer.c>
}

class Lexer : public ::testing::Test
{
public:
  Lexer() : self(0) {}
  virtual void SetUp() {
    ASSERT_FALSE( webvtt_create_parser( &dummyread, &dummyerr, 0, &self ) )
      << "Failed to create parser";
  }

  virtual void TearDown() {
    webvtt_delete_parser( self );
    self = 0;
  }

  webvtt_token lex_newline( const std::string &str, webvtt_uint &pos,
                            bool finished = true ) {
    return webvtt_lex_newline( self, reinterpret_cast<const webvtt_byte *> (
                               str.c_str() ), &pos, str.size(), finished );
  }

private:
  static int WEBVTT_CALLBACK dummyerr( void *userdata, webvtt_uint
                                       line, webvtt_uint col,
                                       webvtt_error error ) {
    return -1;
  }
  static void WEBVTT_CALLBACK dummyread( void *userdata, webvtt_cue *cue ) {}
  webvtt_parser self;
};

/**
 * Test that we correctly return a NEWLINE token when the final buffer ends with
 * a carriage return.
 */
TEST_F(Lexer,LexNewLineCR)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( NEWLINE, lex_newline( "\r", pos ) );
  ASSERT_EQ( 1, pos );
}

/**
 * Test that we correctly identify a single line-feed character as a newline
 */
TEST_F(Lexer,LexNewLineLF)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( NEWLINE, lex_newline( "\n", pos ) );
  ASSERT_EQ( 1, pos );
}

/**
 * Test that we correctly identify a CRLF sequence in the same buffer
 */
TEST_F(Lexer,LexNewLineCRLF)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( NEWLINE, lex_newline( "\r\n", pos ) );
  ASSERT_EQ( 2, pos );
}

/**
 * Test that we correctly identify a CRLF sequence split between two buffers
 */
TEST_F(Lexer,LexNewLineCRLFSplit)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( UNFINISHED, lex_newline( "\r", pos, false ) );
  ASSERT_EQ( 1, pos );
  pos = 0;
  ASSERT_EQ( NEWLINE, lex_newline( "\n", pos, true ) );
  ASSERT_EQ( 1, pos );
}

/**
 * Test that we correctly identify a CR that is not followed by an LF, and
 * backup to the correct position.
 */
TEST_F(Lexer,LexNewLineCRXX)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( NEWLINE, lex_newline( "\rx", pos ) );
  ASSERT_EQ( 1, pos );
}

/**
 * Test that we correctly return BADTOKEN and backup appropriately when we don't
 * encounter a CR or LF
 */
TEST_F(Lexer,LexNewLineXX)
{
  webvtt_uint pos = 0;
  ASSERT_EQ( BADTOKEN, lex_newline( "xxx", pos ) );
  ASSERT_EQ( 0, pos );
}

