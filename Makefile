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

install: all
	@make -C src/ install

.PHONY: all
.PHONY: dirs
.PHONY: clean
.PHONY: install
