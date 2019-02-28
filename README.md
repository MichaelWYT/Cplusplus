# Cplusplus
To compile the code use: 
 - g++ -o <filename.(cpp/h)> -o <filename>

E.g. g++ -o main.cpp -o main

You can also use the make files, which you type: makefile all

This compiles everything within the folder it can find relating to it.

# Makefile not working
If the make file is not working, then you will need to turn it into a bash/shell file. This can be done suing the command chmod a+x <filename>. Files with !/bin/sh should then work.
