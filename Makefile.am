ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src . tests


.PHONY: format
format:
	@cd ./src/ && $(MAKE) $@
	@cd ./tests/ && $(MAKE) $@
