include make_config.mk

ROOTDIR=$(abspath $(DSTDIR))
export ROOTDIR

all: dirs
	@make -C src/

dirs:
	@if [ ! -d $(DSTDIR) ]; then mkdir -v $(DSTDIR); fi;
	@for DIR in $(DIRS); do if [ ! -d "$(DSTDIR)/$$DIR" ]; then mkdir -v -p "$(DSTDIR)/$$DIR"; fi; done;

clean:
	@make -C src/ clean

install:
	@make -C src/ install

.PHONY: all
.PHONY: dirs
.PHONY: clean
.PHONY: install

