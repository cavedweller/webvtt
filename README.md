#libwebvtt
The library for interpreting and authoring conformant WebVTT content
WebVTT is a caption and subtitle format designed for use with HTML5
audio and video elements.

See: [W3C WebVTT Draft](http://dev.w3.org/html5/webvtt/)

[![Build Status](https://travis-ci.org/mozilla/webvtt.png?branch=dev)](https://travis-ci.org/mozilla/webvtt)

##Build Instructions:

In Unix-like environments, we use autotools:

```
./bootstrap.sh && ./configure && make
```

On Windows, we use a Visual Studio Project, see files in build/msvc2010

##Running Tests:

All tests are written using Google Test, and run using `make check`. You can configure the tests to run with our without valgrind, for memory checking.

Without valgrind:

```
./configure
make
make check
```

With valgrind:

```
./configure --enable-valgrind-testing
make
make check
```

When running tests with valgrind, any test that fails valgrind (even if it passes Google Test) will fail. See `test/unit/Makefile.am` for info on known test failures, and how to add/remove them.

##Routines available to application:
### Parser object routines
	webvtt_status webvtt_create_parser( webvtt_cue_fn_ptr, webvtt_error_fn_ptr,
		void *, webvtt_parser * );
	void webvtt_delete_parser( webvtt_parser );
	webvtt_status webvtt_parse_chunk( webvtt_parser, const void *, webvtt_uint );

### String object routines
	webvtt_status webvtt_string_new( webvtt_uint32, webvtt_string * );
	void webvtt_string_delete( webvtt_string );
	webvtt_status webvtt_string_append_utf8( webvtt_string *, const webvtt_byte *,
		webvtt_uint *, webvtt_uint, webvtt_utf8_reader );

### Memory allocation routines
	void *webvtt_alloc( webvtt_uint );
	void *webvtt_alloc0( webvtt_uint );
	void webvtt_free( void * );
	void webvtt_set_allocator( webvtt_alloc_fn_ptr, webvtt_free_fn_ptr, void * );

### Error handling
	const char *webvtt_strerror( webvtt_error );

##TODO:

###General
- Change parser to convert to UTF16 as it goes through the buffer and convert parser to work with UTF16 instead of UTF8.
- node-ffi bindings for libwebvtt structures and public API, to assist with unit testing
- New unit tests, and convert some existing conformance tests to unit tests
- Integration with TravisCI
- Bug fixes
- Thread-safety where needed (Lock before setting global function pointers)
- Reference counting objects (may be a hassle, but would help to prevent leaking
  dropped cue objects)
- Improvements to lexer/parser state machines, in terms of speed and conformance
- Default error handlers when not provided by user
- Internationalized error messages
- Shared-library compilation
- Routines for generating conformant WebVTT text
- Language bindings (Rust, C++, D, etc)
- GNU Autotools build system to enhance portability (With MPL2'd M4 from Mozilla-Central to support Windows environments)

###Cue Text Payload Parsing
- Get shared UTF16 time stamp parser function working in order to create a time stamp node/token.
- Error reporting
- Line and character tracking in the cue_text in order to report errors correctly
- Possible change of token and node data structs to allow easier readability
- MANY bugs

#License
> Copyright (c) 2013 Mozilla Foundation and Contributors
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are
> met:
>
> - Redistributions of source code must retain the above copyright
> notice, this list of conditions and the following disclaimer.
> - Redistributions in binary form must reproduce the above copyright
> notice, this list of conditions and the following disclaimer in the
> documentation and/or other materials provided with the distribution.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
> ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
> LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
> A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
> HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
> SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
> LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
> DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
> THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
> OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

