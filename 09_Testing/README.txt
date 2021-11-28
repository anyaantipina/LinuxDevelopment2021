autoreconf -fisv
./configure --enable-gcov
make
make check
make gcov
make gitclean