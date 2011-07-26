include ../../../make_config.mk
include ../../../defaults.mk

NAME=$(notdir $(abspath ./))
LIB=lib$(NAME).so
LIBS=module/$(LIB)
MODULE_OBJS=$(patsubst %.cpp, %.o, $(wildcard module/*.cpp))

ifneq (,$(findstring admin, $(wildcard *)))
	LIBS+=admin/lib$(NAME).so
	ADMIN_OBJS=$(patsubst %.cpp, %.o, $(wildcard admin/*.cpp))
endif

all: $(LIBS)

module/%.so: $(MODULE_OBJS)
	$(CC) $(LDFLAG) -shared -Wl,-soname,$(notdir $@) $^ -o $@

admin/%.so: $(ADMIN_OBJS)
	$(CC) $(LDFLAG) -shared -Wl,-soname,$(notdir $@) $^ -o $@

.PHONY: all
