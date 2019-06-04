CC = gcc				# Compiler.
CFLAGS = -lcurl -l json-c		# Compiler flags.

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: build 

build:
	$(CC) $(CFLAGS) -o haste haste.c

install: haste
	install -d $(DESTDIR)$(PREFIX)/bin/

clean:
	$(RM) haste
