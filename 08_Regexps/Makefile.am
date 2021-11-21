CFLAGS =-O0 -g

TESTS=tests.sh

tests.sh:
	chmod +x test0.sh

test_all: all
	./test0.sh

bin_PROGRAMS=esub

esub_SOURCES=esub.c

gitclean:
	git clean -fd
