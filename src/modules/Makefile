include ../../make_config.mk
include ../../defaults.mk

all: modules

modules:
	@for FILE in *; do \
		OWN_MAKEFILE=0; \
		if [ -d $$FILE ]; then \
			MODULES="$$MODULES $$FILE"; \
			if [ ! -f $$FILE/Makefile ]; then \
				cp Makefile.template $$FILE/Makefile; \
			else \
				OWN_MAKEFILE=1; \
			fi; \
			make -C $$FILE/ || exit 1; \
			if [ "$$OWN_MAKEFILE" = "0" ]; then rm $$FILE/Makefile; fi; \
		fi; \
	done;

install: all
	@echo "Installing modules"
	@find . -name "*.so" | while read LIB; do \
		MOD_TYPE=$$(basename $$(dirname $$LIB)); \
		LIB_NAME=$$(basename $$LIB); \
		if [ "$$MOD_TYPE" = "admin" ]; then \
			IDIR=panel; \
		else \
			IDIR=modules; \
		fi; \
		$(INSTALL) -v $$LIB $(ROOTDIR)/lib/$$IDIR/$$LIB_NAME; \
	done; 

clean:
	@find . -name "*.*o" | while read FILE; do rm -v $$FILE; done;

.PHONY: all
.PHONY: modules
.PHONY: install
.PHONY: clean
