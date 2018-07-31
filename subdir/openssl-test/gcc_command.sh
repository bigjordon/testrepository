#!/bin/sh
# client
INCLUDE=/home/jordon/workspace/openssl/openssl-1.0.2o/include
LINK=/home/jordon/workspace/openssl/openssl-1.0.2o/
#gcc  -I$INCLUDE cli.cpp  libssl.a libcrypto.a -ldl -o client.bin
gcc  -I$INCLUDE -L$LINK cli.cpp  -lssl -lcrypto -ldl -o client.bin
# -ldl should at last position of the link option

#server
gcc  -I$INCLUDE -L$LINK serv.cpp  -lssl -lcrypto -ldl -o server.bin
