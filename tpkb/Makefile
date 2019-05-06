ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

tpkb: tp.cpp hid.o hidapi.h
	g++ -o tpkb tp.cpp hid.o -framework CoreFoundation -framework IOKit

hid.o: hid.c hidapi.h
	gcc -c -o hid.o hid.c

.PHONY: install
install: tpkb
	install -m 0755 $? $(PREFIX)/bin/tpkb

.PHONY: clean
clean:
	-rm -rf tpkb *.o
