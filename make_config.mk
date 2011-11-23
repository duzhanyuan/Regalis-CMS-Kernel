#
# Copyright (c) by Patryk Jaworski
# Contact:
#  -> E-mail: Patryk Jaworski <skorpion9312@gmail.com>
#  -> XMPP/Jabber: Patryk Jaworski <skorpion9312@jabber.org>
#

CC = g++
CFLAGS = -Wall -Os -rdynamic -fPIC
CFLAGS += -I/usr/include/mysql++ -I/usr/include/mysql
LDFLAGS = -rdynamic
DSTDIR ?= bin
DIRS = lib/modules lib/admin lib/content-types etc/modules etc/modules/install etc/content-types/install var/log usr/share/locale
INSTALL=install -Dm 744
AUTHOR=Patryk Jaworski
AUTHOR_EMAIL=skorpion9312@gmail.com
