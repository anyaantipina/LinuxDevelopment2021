LIBRARIES = remove.so
BINARIES = move
SOURCES = move.c
LIB_SOURCES = remove.c
SHARED_LIB = remove
TEST_HELPER = diff tmp template ; rm template tmp
STRACE_RETURN_CODE_EXTRACTOR = tail -n1 trace | cut -d' ' -f4 | cmp code ; rm trace code

all:	$(BINARIES)

remove:
	cc -shared -Wl,--no-as-needed -ldl $(LIB_SOURCES) -o $(SHARED_LIB).so

move:	move.o
	cc  -g move.c -o move

test_0: move
	echo "TEST 0. Result shoul be: FILE1 DOESN't EXIST; FILE2 ESIXTS"
	echo "asdf\njfgh123" > file1
	-strace ./move file1 file2 2> trace
	echo 0 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "find: ‘file1’: No such file or directory" 2> template; find file1 > tmp; $(TEST_HELPER)
	echo "file2" > template; find file2 > tmp; $(TEST_HELPER)
	rm file2

test_1: move
	echo "TEST 1. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace ./move file1 2> trace
	echo 1 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_2: move
	echo "TEST 2. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace ./move file file2 2> trace
	echo 2 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1


test_3: move
	echo "TEST 3. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace -P file2 -eopenat -efault=openat:error=EPERM ./move file1 file2 2> trace
	echo 3 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_4: move
	echo "TEST 4. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace -P file1 -eread -efault=read:error=EPERM ./move file1 file2 2> trace
	echo 4 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_5: move
	echo "TEST 5. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace -eclose -efault=close:error=EPERM ./move file1 file2 2> trace
	echo 5 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_6: move
	echo "TEST 6. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace -eclose -efault=close:error=EPERM:when=4 ./move file1 file2 2> trace
	echo 6 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_7: move
	echo "TEST 7. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > file1
	-strace -P file1 -eunlink -efault=unlink:error=EPERM ./move file1 file2 2> trace
	echo 7 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "file1" > template; find file1 > tmp; $(TEST_HELPER)
	echo "find: ‘file2’: No such file or directory" 2> template; find file2 > tmp; $(TEST_HELPER)
	rm file1

test_preload: move remove
	echo "TEST 7. Result shoul be: FILE1 EXISTS; FILE2 DOESN'T ESIXT"
	echo "asdf\njfgh123" > filePROTECT1
	-LD_PRELOAD=./remove.so strace ./move filePROTECT1 file2 2> trace
	echo 111 > code ; $(STRACE_RETURN_CODE_EXTRACTOR)
	echo "filePROTECT1" > template; find filePROTECT1 > tmp; $(TEST_HELPER)
	echo "file2" > template; find file2 > tmp; $(TEST_HELPER)
	rm filePROTECT1 file2

clean:
	rm -f $(SOURCES:.c=.o) $(BINARIES) $(LIBRARIES)

strace_tests:	test_0 test_1 test_2 test_3 test_4 test_5 test_6 test_7

test:	strace_tests test_preload
