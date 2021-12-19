autoreconf -fisv   
./configure   
make   
./src/guess_the_number   
   
NB! On my computer, the directory with the .mo file is called "ru_RU/LC_MESSAGES/".   
It may be different on yours. Use ltrace to find which directory to search in.