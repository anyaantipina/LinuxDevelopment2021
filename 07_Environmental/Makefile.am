CFLAGS =-O0 -g

TESTS=tests.sh

tests.sh:
	chmod +x test0.sh
	chmod +x test_file.sh
	chmod +x test_string.sh

test_all: all
	./test0.sh
	./test_file.sh
	./test_string.sh

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

gitclean:
	git clean -fd
