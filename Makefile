CC = gcc								# Compiler.
CFLAGS = $(shell pkg-config --libs json-c libcurl) -lcurl		# Compiler flags.

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: build 

build:
	$(CC) $(CFLAGS) -o haste haste.c

install: haste
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f haste $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/haste
	@echo Haste client has been installed to '$(DESTDIR)$(PREFIX)/bin/haste'.

clean:
	$(RM) haste
