AC_INIT([vgmreader], [0.1], [cybermats@gmail.com])

AC_CONFIG_AUX_DIR([build_aux])
AC_CONFIG_SRCDIR([src])
AM_PROG_AR
AM_INIT_AUTOMAKE([-Wall foreign])

AC_CONFIG_MACRO_DIRS([m4])

AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_AWK

PKG_CHECK_MODULES([CRITERION], [criterion])

AC_SUBST([CRITERION_FLAGS])
AC_SUBST([CRITERION_LIBS])

AC_CHECK_HEADERS([stdlib.h zlib.h argp.h])

AC_FUNC_MALLOC

AC_SEARCH_LIBS(deflate, z)
AC_SEARCH_LIBS(argp_parse,argp)

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 tests/Makefile])
		 
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AC_OUTPUT
