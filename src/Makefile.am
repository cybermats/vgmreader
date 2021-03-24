AM_CPPFLAGS = -I${top_srcdir}/src

HFILES =\
	vgm.h

CFILES =\
	vgm.c


lib_LTLIBRARIES = libvgmreader.la
libvgmreader_la_SOURCES = $(CFILES) $(HFILES)

bin_PROGRAMS = vgmreader
vgmreader_SOURCES = main.c
vgmreader_LDADD = libvgmreader.la
