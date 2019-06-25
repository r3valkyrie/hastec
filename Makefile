CC = gcc
CFLAGS = -march=native -O2 -std=c11 $(shell pkg-config --libs json-c libcurl)

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: build 

build:
	$(CC) -o haste haste.c $(CFLAGS)

install: haste
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f haste $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/haste
	@echo Haste client has been installed to '$(DESTDIR)$(PREFIX)/bin/haste'.

clean:
	$(RM) haste
