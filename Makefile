#
# Copyright (c) by Patryk Jaworski
# Contact:
#  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
#  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
#

include make_config.mk

ROOTDIR=$(abspath $(DSTDIR))
export ROOTDIR

all: dirs
	@make -C src/

dirs:
	@if [ ! -d $(ROOTDIR) ]; then mkdir -v $(ROOTDIR); fi;
	@for DIR in $(DIRS); do if [ ! -d "$(ROOTDIR)/$$DIR" ]; then mkdir -v -p "$(ROOTDIR)/$$DIR"; fi; done;

clean:
	@make -C src/ clean

install: all data
	@make -C src/ install
	@make -C src/ translations

data:
	@echo "Installing default data files"
	cp -ruv src/data/* $(ROOTDIR)/

.PHONY: all clean dirs install translations data

