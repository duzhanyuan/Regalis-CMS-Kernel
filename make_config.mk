CC = g++
CFLAGS = -Wall -Os -rdynamic -fPIC
LDFLAGS = -rdynamic
DSTDIR ?= bin
DIRS = lib/modules lib/panel lib/content-types etc/modules etc/content-types
INSTALL=install -Dm 744

