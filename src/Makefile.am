#AM_CPPFLAGS = -I${top_srcdir}/src
ACLOCAL_AMFLAGS = -I m4

HFILES =\
	vgm.h \
	args.h \
	decode.h

CFILES =\
	vgm.c \
	args.c \
	decode.c


lib_LTLIBRARIES = libvgmreader.la
libvgmreader_la_SOURCES = $(CFILES) $(HFILES)

bin_PROGRAMS = vgmreader
vgmreader_SOURCES = main.c
vgmreader_LDFLAGS = -static
vgmreader_LDADD = libvgmreader.la
