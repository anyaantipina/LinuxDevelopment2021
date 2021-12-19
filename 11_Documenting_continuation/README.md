autoreconf -fisv   
./configure   
make   
./src/guess_the_number   
   
man -l doxygen-doc/man/man1/guess_the_number.c.1   
   
NB! On my computer, the directory with the .mo file is called "ru_RU/LC_MESSAGES/".   
It may be different on yours. Use ltrace to find which directory to search in.
   
Earlier, I encountered an error when trying to connect doxygen to autotools and    
therefore could not finish my homework on time.   
Now I found an error -- it consisted in the fact that the autoconf-archive package was missing on my linux

I couldn't translate help because the macro gettext doesn't work in variables for argp. The compiler swears at them
