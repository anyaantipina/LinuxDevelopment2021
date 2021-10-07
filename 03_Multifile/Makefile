LIBRARIES = liboutput.so liboutput_static.a
BINARIES = prog prog-a prog-so
CFLAGS = -g
SOURCES = $(wildcard *.c)
LIB_SOURCES = $(wildcard fun.c const.c)
STATIC_LIB = output_static
SHARED_LIB = output

all:	$(BINARIES)

%.o:    %.c
	cc $< -c -o $@

README: prog
	./$< 2> $@

static_lib: 
	cc -c $(LIB_SOURCES)
	ar -rcs lib$(STATIC_LIB).a $(LIB_SOURCES:.c=.o)
	rm -f $(LIB_SOURCES:.c=.o)

shared_lib:
	cc -fPIC -shared $(LIB_SOURCES) -o lib$(SHARED_LIB).so

prog:	const.o fun.o prog.o
		cc $^ -o $@

prog-a:	prog.o static_lib
		cc -static prog.o -l$(STATIC_LIB) -L. -o prog-a

prog-so: prog.o shared_lib
		cc prog.o -L. -l$(SHARED_LIB) -o prog-so

test_0: all
	./prog >test.out 2>&1
	./prog-a >test-a.out 2>&1
	LD_LIBRARY_PATH=$(PWD) ./prog-so >test-so.out 2>&1
	cmp test-a.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test-a.out >cmp.out 2>&1; cat cmp.out
	rm -rf *out


test_1: all
	./prog 1 >test.out 2>&1
	./prog-a 1 >test-a.out 2>&1
	LD_LIBRARY_PATH=$(PWD) ./prog-so 1 >test-so.out 2>&1
	cmp test-a.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test-a.out >cmp.out 2>&1; cat cmp.out
	rm -rf *.out


test_3: all
	./prog 1 2 3 >test.out 2>&1
	./prog-a 1 2 3 >test-a.out 2>&1
	LD_LIBRARY_PATH=$(PWD) ./prog-so 1 2 3 >test-so.out 2>&1
	cmp test-a.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test.out >cmp.out 2>&1; cat cmp.out
	cmp test-so.out test-a.out >cmp.out 2>&1; cat cmp.out
	rm -rf *.out

clean:
	rm -f $(SOURCES:.c=.o) *.err *.out

distclean: clean
	rm -f $(BINARIES) $(LIBRARIES)

test:	test_0 test_1 test_3 distclean
