AM_CPPFLAGS = -I${top_srcdir}/src

TESTS = check_vgmreader
check_PROGRAMS = check_vgmreader
check_vgmreader_SOURCES = check_main.c \
			check_core.c \
			check_header.c
check_vgmreader_CFLAGS = @CHECK_CFLAGS@
check_vgmreader_LDADD = $(top_builddir)/src/libvgmreader.la @CHECK_LIBS@
