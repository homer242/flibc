flc_includedir = $(top_srcdir)/include/flc

ACLOCAL_AMFLAGS = -I m4 --install
AUTOMAKE_OPTIONS = foreign

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = flc.pc

pkginclude_HEADERS = $(flc_includedir)/dict.h \
		     $(flc_includedir)/flc.h \
		     $(flc_includedir)/list.h \
		     $(flc_includedir)/math.h \
		     $(flc_includedir)/string.h

SUBDIRS = src tests
