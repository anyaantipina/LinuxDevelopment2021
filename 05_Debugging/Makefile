BINARIES = range
SOURCES = $(wildcard *.c)

all:	$(BINARIES)

range:
		cc  -g -O0 range.c -o range

test: all
	gdb -x gdb_script_1 --batch --quiet --args ./range 1 12 | grep "@@@" | cut -d' ' -f2- | cmp pattern_1.txt
	gdb -x gdb_script_2 --batch --quiet --args ./range -100 100 3 | grep "@@@" | cut -d' ' -f2- | cmp pattern_2.txt

clean:
	rm -f $(BINARIES) $(SOURCES:.c=.o)

