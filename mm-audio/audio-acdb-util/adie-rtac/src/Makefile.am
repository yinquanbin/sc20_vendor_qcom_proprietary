AM_CFLAGS = -Wundef \
        -Wstrict-prototypes \
        -Wno-trigraphs \
        -g -O0 \
        -fno-inline \
        -fno-short-enums \
        -fpic \
        -Dstrlcat=g_strlcat

AM_CPPFLAGS = -I../inc \
               $(AUDIOALSA_CFLAGS) \
               $(AUDCAL_CFLAGS) \
              -I.

h_sources = ../inc/adie-rtac.h

c_sources = adie-rtac.c

library_includedir = $(pkgincludedir)
library_include_HEADERS = $(h_sources)

lib_LTLIBRARIES = libadiertac.la
libadiertac_la_CC = @CC@
libadiertac_la_SOURCES = $(c_sources) $(h_sources)
libadiertac_la_CFLAGS = $(AM_CFLAGS) -DUSE_GLIB @GLIB_CFLAGS@ -D CDC_REG_DIG_BASE_READ=0x200 -D CDC_REG_DIG_OFFSET=0x000 -D CDC_REG_DIG_BASE_WRITE=0x200
libadiertac_la_CPPFLAGS = $(AM_CPPFLAGS) -DUSE_GLIB @GLIB_CFLAGS@
libadiertac_la_LDFLAGS = $(AUDCAL_LIBS) @GLIB_LIBS@ -shared -version-info 1:0:0
