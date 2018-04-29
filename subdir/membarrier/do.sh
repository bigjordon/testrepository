#!/bin/sh
rm a.out
gcc -O2 membarrier.c
gdb a.out
