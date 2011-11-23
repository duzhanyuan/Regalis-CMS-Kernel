#
# Copyright (c) by Patryk Jaworski
# Contact:
#  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
#  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
#

include ../../make_config.mk
include ../../defaults.mk

DEPS=$(wildcard */*.dep)

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

install: all deps sql
	@echo "Installing modules"
	@find . -name "*.so" | while read LIB; do \
		MOD_TYPE=$$(basename $$(dirname $$LIB)); \
		LIB_NAME=$$(basename $$LIB); \
		if [ "$$MOD_TYPE" = "admin" ]; then \
			IDIR=admin; \
		else \
			IDIR=modules; \
		fi; \
		$(INSTALL) -v $$LIB $(ROOTDIR)/lib/$$IDIR/$$LIB_NAME; \
	done; 

deps: $(DEPS)
	@for DEP in $^; do \
		$(INSTALL) -v $$DEP "$(ROOTDIR)/etc/modules/$$(basename $$(dirname $$DEP)).dep"; \
	done;

sql:
	@echo "Copying install SQL scripts..."
	@find . -name "install.sql" | while read SQL; do \
		MODULE=$$(basename $$(dirname "$$SQL")); \
		$(INSTALL) -v "$$SQL" "$(ROOTDIR)/etc/modules/install/$$MODULE.sql"; \
	done;

clean:
	@find . -name "*.*o" | while read FILE; do rm -v $$FILE; done;

.PHONY: all
.PHONY: modules
.PHONY: install
.PHONY: clean
.PHONY: deps
