ACLOCAL_AMFLAGS = -I m4 --install
dist_doc_DATA = README
pkgconfigdir = $(libdir)/pkgconfig
dist_pkgconfig_DATA = pfxtree.pc

include_HEADERS = pfxtree.h
lib_LTLIBRARIES = libpfxtree.la

libpfxtree_la_SOURCES = pfxtree.c
libpfxtree_la_LDFLAGS = -version-info 2:0:2
libpfxtree_la_CFLAGS = -Wall -Wextra -Wunreachable-code -ftrapv -std=c89

AM_CFLAGS = $(DEPS_CFLAGS)
AM_LIBS = $(DEPS_LIBS)
