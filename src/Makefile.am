include $(top_srcdir)/flymake.mk

#AM_CPPFLAGS = -I${top_srcdir}/src
ACLOCAL_AMFLAGS = -I m4

HFILES =\
	vgm.h \
	args.h \
	decode.h \
	vgm_helper.h

CFILES =\
	vgm.c \
	args.c \
	decode.c \
	vgm_helper.c



bin_PROGRAMS = vgmreader
vgmreader_SOURCES = main.c $(CFILES) $(HFILES)


.PHONY: format
format:
	clang-format --style=Google -i $(CFILES) $(HFILES)

.PHONY: check-syntax
check-syntax:
	@s=$(suffix $(CHK_SOURCES)); \
	if [ "$$s" = ".c"  ]; then $(call get_cs_cmdline,C)  $(CHK_SOURCES);\
	else exit 1; fi
