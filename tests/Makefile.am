AM_CPPFLAGS = -I${top_srcdir}/src
ACLOCAL_AMFLAGS = -I m4

HFILES =\
	check_check.h

CFILES =\
	check_main.c \
	check_core.c \
	check_header.c

CLEANFILES = *~ *.tap

TESTS = check_vgmreader
check_PROGRAMS = check_vgmreader
check_vgmreader_SOURCES = $(CFILES) $(HFILES)
check_vgmreader_CFLAGS = @CHECK_CFLAGS@
check_vgmreader_LDADD = $(top_builddir)/src/libvgmreader.la @CHECK_LIBS@
