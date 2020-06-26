.PHONY: all clean docs maintainer-clean install uninstall

PREFIX=/usr/local

CFLAGS=-shared -fPIC -Wall -Werror -pedantic-errors `pkg-config --cflags libxml-2.0`

ifeq ($(DEBUG),1)
	CFLAGS+=-g
else
	CFLAGS+=-O3
endif

LDFLAGS=`pkg-config --libs libxml-2.0`

all: libxpath2.so

libxpath2.so: libxpath2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

docs:
	$(MAKE) -C doc

clean:
	rm -f libxpath2.so

maintainer-clean: clean
	$(MAKE) -C doc clean

install:
	cp libxpath2.so $(PREFIX)/lib
	cp libxpath2.h $(PREFIX)/include
	cp libxpath2.pc $(PREFIX)/lib/pkgconfig

uninstall:
	rm $(PREFIX)/lib/libxpath2.so
	rm $(PREFIX)/include/libxpath2.h
	rm $(PREFIX)/lib/pkgconfig/libxpath2.pc
