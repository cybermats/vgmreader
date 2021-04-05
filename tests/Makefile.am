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

SRC_DIR=$(top_srcdir)/src
VPATH=$(SRC_DIR)

C_SRCFILES = $(SRC_DIR)/vgm.c \
	$(SRC_DIR)/args.c \
	$(SRC_DIR)/decode.c \
	$(SRC_DIR)/vgm_helper.c \
	$(SRC_DIR)/vgm_config.c

HFILES =

CFILES = \
	main.c \
	test_core.c \
	test_header.c \
	test_decoder.c \
	test_commands.c \
	test_process_commands.c

check_PROGRAMS = criterion_tests
criterion_tests_SOURCES = $(CFILES) $(C_SRCFILES) $(H_SRCFILES)
criterion_tests_CFLAGS =  $(CRITERION_CFLAGS)
criterion_tests_LDFLAGS =  $(CRITERION_LIBS) -static

TESTS = criterion_tests


.PHONY: format
format:
	clang-format --style=Google -i $(CFILES) $(HFILES)

.PHONY: check-syntax
check-syntax:
	@s=$(suffix $(CHK_SOURCES)); \
	if [ "$$s" = ".c"  ]; then $(call get_cs_cmdline,C) -I../src $(CHK_SOURCES);\
	else exit 1; fi
