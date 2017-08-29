#!/bin/sh
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH
#      libss.so as argv1
./main libss.so
