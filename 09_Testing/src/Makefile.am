CFLAGS = -ansi -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
libbuf_la_SOURCES = libbuf.c
libbuf_la_LDFLAGS = -version-info 0:0:0

buf_LDADD = libbuf.la

gcov:
	gcov -o .libs libbuf -k -j | grep "Lines executed"
