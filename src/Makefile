include ../make_config.mk
include ../defaults.mk
KERNEL_LIBS = -ldl -lboost_filesystem -lboost_system
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp */*.cpp))

all: index.cgi modules

modules:
	@make -C modules/

index.cgi: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(KERNEL_LIBS)

clean:
	@for OBJ in $(OBJS); do \
		if [ -e $$OBJ ]; then \
			rm -v "$$OBJ"; \
		fi; \
	done;
	@rm -v index.cgi
	@make -C modules/ clean

install: all
	$(INSTALL) index.cgi $(ROOTDIR)/index.cgi
	@make -C modules/ install
	

.PHONY: all
.PHONY: clean
.PHONY: install
.PHONY: modules
