autoreconf -fisv
./configure

I don't know why, I can't generate the doxy file, configure.ac swears at his PROJECT_NAME

make
./src/guess_the_number

I couldn't add translation to --help, for some reason the compiler swears at expanding macros ("_") inside strings in variables for argp.