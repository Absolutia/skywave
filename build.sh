#! /bin/bash
# Use this shell script to automate the act of compiling.
# 	Note: you will want to replace $$ with the path of of the include sub-
# directory, which contains the headers containing much of the actual functions.

g++ -Wall main.cpp -lncursesw -pthread -I $$
