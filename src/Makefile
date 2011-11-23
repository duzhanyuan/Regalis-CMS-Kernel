#
# Copyright (c) by Patryk Jaworski
# Contact:
#  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
#  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
#

include ../make_config.mk
include ../defaults.mk
KERNEL_LIBS = -ldl -liniparser -lmysqlpp
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp */*.cpp))
SRCS = $(wildcard *.hpp *.cpp modules/*.hpp modules/*.cpp)
MOS = $(patsubst %.po, %.mo, $(wildcard po/translations/*/*.po))

all: index.cgi modules $(MOS)

pot: $(SRCS)
	@if [ ! -d po/ ]; then mkdir -v po/; fi;
	@for FILE in $^; do echo "$$FILE" >> po/list; done;
	xgettext -f po/list -o po/kernel.pot -C -c -k_ -n --no-wrap --copyright-holder="$(AUTHOR) <$(AUTHOR_EMAIL)>" --package-name="Regalis CMS" --package-version="$$(cat VERSION)" --from-code=utf-8
	@rm po/list

%.mo: %.po
	msgfmt $< -o $@

translations: $(MOS)
	@for MO in $(MOS); do \
		MO_LANG="$$(basename $$(dirname $$MO))"; \
		MO_NAME="$$(basename $$MO)"; \
		$(INSTALL) -v $$MO $(ROOTDIR)/usr/share/locale/$$MO_LANG/LC_MESSAGES/$$MO_NAME; \
	done;

modules:
	@make -C modules/

index.cgi: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(KERNEL_LIBS) -o $@

clean:
	@for OBJ in $(OBJS); do \
		if [ -e $$OBJ ]; then \
			rm -v "$$OBJ"; \
		fi; \
	done;
	@rm -v index.cgi
	@make -C modules/ clean

install: all translations
	$(INSTALL) index.cgi $(ROOTDIR)/index.cgi
	@make -C modules/ install

.PHONY: all clean install modules translations
