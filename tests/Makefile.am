include $(top_srcdir)/flymake.mk

# use the TAP log driver
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
            $(top_srcdir)/build-aux/tap-driver.sh

 # Setup Criterion TAP output using ENV
 AM_TESTS_ENVIRONMENT = \
    CRITERION_OUTPUTS='tap:-'; \
    export CRITERION_OUTPUTS;

AM_CPPFLAGS = -I${top_srcdir}/src $(CRITERION_CFLAGS)
ACLOCAL_AMFLAGS = -I m4

HFILES =

CFILES = \
	main.c \
	test_core.c \
	test_header.c \
	test_decoder.c

check_PROGRAMS = criterion_tests
criterion_tests_SOURCES = $(CFILES) $(C_SRCFILES) $(H_SRCFILES)
criterion_tests_CFLAGS =  $(CRITERION_CFLAGS)
criterion_tests_LDFLAGS =  $(CRITERION_LIBS) -static
criterion_tests_LDADD = $(top_builddir)/src/libvgmreader.la

TESTS = criterion_tests


.PHONY: format
format:
	clang-format -i $(CFILES) $(HFILES)

.PHONY: check-syntax
check-syntax:
	@s=$(suffix $(CHK_SOURCES)); \
	if [ "$$s" = ".c"  ]; then $(call get_cs_cmdline,C)  $(CHK_SOURCES);\
	else exit 1; fi
