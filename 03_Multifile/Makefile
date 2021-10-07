LIBRARIES = liboutput.so liboutput_static.a
BINARIES = prog prog-a prog-so
CFLAGS = -g
SOURCES = $(wildcard *.c)
LIB_SOURCES = $(wildcard fun.c const.c)
STATIC_LIB = output_static
SHARED_LIB = output

all:	$(BINARIES)

static_lib: 
	cc -c $(LIB_SOURCES)
	ar -rcs lib$(STATIC_LIB).a $(LIB_SOURCES:.c=.o)
	rm -f $(LIB_SOURCES:.c=.o)

shared_lib:
	cc -fPIC -shared $(LIB_SOURCES) -o lib$(SHARED_LIB).so

prog:	const.o fun.o prog.o
		cc const.o fun.o prog.o -o prog

prog-a:	prog.o static_lib
		cc -static prog.o -l$(STATIC_LIB) -L. -o prog-a

prog-so: prog.o shared_lib
		cc prog.o -L. -l$(SHARED_LIB) -o prog-so

test_0: all
	./prog 1>test.out 2>test.err
	./prog-a 1>test-a.out 2>test-a.err
	LD_LIBRARY_PATH=$(PWD) ./prog-so 1>test-so.out 2>test-so.err
	cmp test-a.out test.out
	cmp test-so.out test.out
	cmp test-so.out test-a.out
	cmp test-a.err test.err
	cmp test-so.err test.err
	cmp test-so.err test-a.err
	rm -rf *.out *.err

test_1: all
	./prog 1 1>test.out 2>test.err
	./prog-a 1 1>test-a.out 2>test-a.err
	LD_LIBRARY_PATH=$(PWD) ./prog-so 1 1>test-so.out 2>test-so.err
	cmp test-a.out test.out
	cmp test-so.out test.out
	cmp test-so.out test-a.out
	cmp test-a.err test.err
	cmp test-so.err test.err
	cmp test-so.err test-a.err
	rm -rf *.out *.err

test_3: all
	./prog 1 2 3 1>test.out 2>test.err
	./prog-a 1 2 3 1>test-a.out 2>test-a.err
	LD_LIBRARY_PATH=$(PWD) ./prog-so 1 2 3 1>test-so.out 2>test-so.err
	cmp test-a.out test.out
	cmp test-so.out test.out
	cmp test-so.out test-a.out
	cmp test-a.err test.err
	cmp test-so.err test.err
	cmp test-so.err test-a.err
	rm -rf *.out *.err

clean:
		rm -f $(SOURCES:.c=.o) $(BINARIES) $(LIBRARIES) *.err *.out

test:	test_0 test_1 test_3 clean
