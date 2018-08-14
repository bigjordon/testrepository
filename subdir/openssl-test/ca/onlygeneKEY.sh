#!/bin/sh
#

#prepare
KEY_OUT_DIR="./key_out"
if [ ! -d $KEY_OUT_DIR ];then
	mkdir -p $KEY_OUT_DIR
fi
cd $KEY_OUT_DIR

############################## Generate begin ##############################################

### First generate the private key
# encrypt the key
#openssl genrsa -aes256 -passout pass:111111 -out server.key 2048
# no encrypt
echo "=====generate rsa_private.key begin======\n"
openssl genrsa -out rsa_private.key 2048
echo "=====generate rsa_private.key done======\n\n\n"

# show private key
echo "=====show rsa_private.key begin======\n"
openssl rsa -in rsa_private.key -noout -text
echo "=====show rsa_private.key done======\n\n\n"

# generate public key
echo "=====generate rsa_public.key begin======\n"
openssl rsa -in rsa_private.key -pubout -out rsa_public.key
echo "=====generate rsa_public.key done======\n\n\n"

# show public key
echo "=====show rsa_public.key begin======\n"
openssl rsa -pubin -in rsa_public.key -noout -text
echo "=====show rsa_public.key done======\n\n\n"

