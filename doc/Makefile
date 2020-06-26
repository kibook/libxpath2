PREFIX=/usr/local

all: libxpath2.3 ../README.md

libxpath2.3: DMC-LIBXPATH2-A-00-00-00-00A-040A-D_EN-CA.XML
	s1kd2db $< | pandoc -f docbook -t man -s -o $@

../README.md: DMC-LIBXPATH2-A-00-00-00-00A-040A-D_EN-CA.XML
	s1kd2db $< | pandoc -f docbook -t markdown_github -s -o $@

clean:
	rm -f libxpath2.3

install:
	cp libxpath2.3 $(PREFIX)/share/man/man3

uninstall:
	rm $(PREFIX)/share/man/man3/libxpath2.3
