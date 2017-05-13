CC=c99
CFLAGS=-Wall -Wextra -Wunreachable-code -ftrapv -fPIC -g -D_POSIX_C_SOURCE=2
PREFIX=/usr/local
LIBDIR=$(DESTDIR)$(PREFIX)/lib
PKGCONFIGDIR=$(LIBDIR)/pkgconfig
HDIR=$(DESTDIR)$(PREFIX)/include

MAJOR=0
MINOR=3
REVISION=0
VERSION=$(MAJOR).$(MINOR).$(REVISION

all: libpfxtree.so libpfxtree.a

libpfxtree_deps=pfxtree.o
libpfxtree.a: $(libpfxtree_deps)
	$(AR) rcs $@ $(libpfxtree_deps)

libpfxtree.so: $(libpfxtree_deps)
	$(CC) -shared -o $@ $(libpfxtree_deps)

pfxtree_test_deps=pfxtree-test.o libpfxtree.a
pfxtree-test: $(pfxtree_test_deps)
	$(CC) -o $@ $(pfxtree_test_deps)

test: pfxtree-test
	./pfxtree-test

install: libpfxtree.so
	install -m755 libpfxtree.so $(LIBDIR)/libpfxtree.so.$(VERSION)
	install -m644 pfxtree.h $(HDIR)/pfxtree.h
	install -m644 pfxtree.pc $(PKGCONFIGDIR)/pfxtree.pc
	ln -s $(LIBDIR)/libpfxtree.so.$(VERSION) $(LIBDIR)/libpfxtree.so.$(MAJOR)
	ln -s $(LIBDIR)/libpfxtree.so.$(VERSION) $(LIBDIR)/libpfxtree.so
