AM_CPPFLAGS = -I${top_srcdir}/src

lib_LTLIBRARIES = libvgmreader.la
libvgmreader_la_SOURCES = vgm.c

bin_PROGRAMS = vgmreader
vgmreader_SOURCES = main.c
vgmreader_LDADD = libvgmreader.la
