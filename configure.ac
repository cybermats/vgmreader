AC_PREREQ([2.61])
AC_INIT([vgmreader], [0.1], [cybermats@gmail.com])
AM_PROG_AR

AC_CONFIG_SRCDIR([src/main.c])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects foreign])

AC_PROG_CC
AC_PROG_LIBTOOL

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AM_PROG_CC_C_O

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h zlib.h check.h])

AC_FUNC_MALLOC

AC_SEARCH_LIBS(deflate, z)

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 tests/Makefile])
AC_OUTPUT
