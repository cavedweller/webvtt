#Install locations
webvttincludedir = $(includedir)/webvtt

#Mangled config file
BUILT_SOURCES = webvtt-config.h

$(top_builddir)/include/webvtt:
	@$(mkdir_p) $@

webvtt-config.h: $(top_builddir)/config.h | $(top_builddir)/include/webvtt
	@cat $< | sed "s/#define \([[:alpha:]_]\{1,\}\)/#define WEBVTT_\1/" > $@

#C API headers
webvttinclude_HEADERS = \
  webvtt-config.h \
  webvtt-config-win32.h \
  cue.h \
  error.h \
  parser.h \
  string.h \
  util.h
