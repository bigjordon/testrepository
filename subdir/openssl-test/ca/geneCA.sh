#!/bin/sh
#

#prepare
CA_OUT_DIR="./ca_out"
if [ ! -d $CA_OUT_DIR ];then
	mkdir -p $CA_OUT_DIR
fi
cd $CA_OUT_DIR

############################## Generate begin ##############################################

### First generate the private key
# encrypt the key
#openssl genrsa -aes256 -passout pass:111111 -out server.key 2048
# no encrypt
openssl genrsa -out server.key 2048
echo "=====generate server.key done======\n"

### Second generate Certificate Signing Request csr file
openssl req -new -key server.key -out server.csr
echo "=====generate server.csr done======\n"

### Optional examin the csr
openssl req -in server.csr -text -noout -subj "/C=VE/ST=VE/L=VE/O=VE/OU=VE/CN=nono.com/emailAddress=nono@nono.com"
echo "=====show server.csr done======\n"

### Wait I need has a CA certifcate to sign the ca requeset
### -x509 option means generate self-signed ca, I can use other private keys for -key option
openssl req -new -x509 -key server.key -out ca.crt -days 365 -subj "/C=CA/ST=CA/L=CA/O=CA/OU=CA/CN=ca.com/emailAddress=CA@ca.com"
echo "=====generate ca.crt done======\n"

### Optoinal show ca
openssl x509 -in ca.crt -noout -text
echo "=====show ca.crt done======\n"

### Third use the CA's ca.cer and CA's key to sign the csr 
# node -CAkey need use CA's private key, here i am CA so use server.key
openssl x509 -req -days 365 -in server.csr -CA ca.crt -CAkey server.key -CAcreateserial -out server.crt
echo "=====generate server.crt done======\n"

### Optional show server ca
openssl x509 -in server.crt -text -noout
echo "=====show server.crt done======\n"
############################## Generate end ##############################################

# verfy the CA 
# openssl verify  to verify the CA untill the self signed CA
# openssl verify -CApath the path to save CAa
#                        in the path are symbol link of CAs, the symbal link must be the hash of the CA's subject name
#                        use openssl x509 -hash (or -subject_hash) -in CA.crt
#                        and still we can use `c_rehash CAPATH` to auto generate the symbol link of the CAs to the path

# to verity the CA we need generate the CA DIR first. since the ca.crt is the self-signed certificate(no nedd)
openssl verify ca.crt # use ca dir is better
echo "=====verify ca.crt done======\n"

# generate the CA dirs
c_rehash .
echo "=====ca dir build done======\n"
# verify the server.crt
openssl verify -CApath . server.crt
echo "=====server.crt verify done======\n"
