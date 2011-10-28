flc_includedir = $(top_srcdir)/include/flibc

ACLOCAL_AMFLAGS = -I m4 --install
AUTOMAKE_OPTIONS = foreign

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = flibc.pc

pkginclude_HEADERS = $(flc_includedir)/dict.h \
		     $(flc_includedir)/flibc.h \
		     $(flc_includedir)/list.h \
		     $(flc_includedir)/math.h \
		     $(flc_includedir)/log.h \
		     $(flc_includedir)/string.h

SUBDIRS = src tests
