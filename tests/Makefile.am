INCLUDES = -I$(top_srcdir)/include

TESTS = test_str test_log

check_PROGRAMS = $(TESTS)

test_str_SOURCES = test_str.c
test_str_LDADD = $(top_srcdir)/src/libflibc.la

test_log_SOURCES = test_log.c
test_log_LDADD = $(top_srcdir)/src/libflibc.la
