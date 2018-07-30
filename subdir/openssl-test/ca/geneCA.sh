#!/bin/sh
#
### First generate the private key
# encrypt the key
#openssl genrsa -aes256 -passout pass:111111 -out server.key 2048
# no encrypt
openssl genrsa -out server.key 2048

### Second generate Certificate Signing Request csr file
openssl req -new -key server.key -out server.csr

### Optional examin the csr
openssl req -in server.csr -text -noout -subj "/C=VE/ST=VE/L=VE/O=VE/OU=VE/CN=nono.com/emailAddress=nono@nono.com"

### Wait I need has a CA certifcate to sign the ca requeset
### -x509 option means generate self-signed ca, I can use other private keys for -key option
openssl req -new -x509 -key server.key -out ca.crt -days 365 -subj "/C=CA/ST=CA/L=CA/O=CA/OU=CA/CN=ca.com/emailAddress=CA@ca.com"

### Third use the CA's ca.cer and CA's key to sign the csr 
# node -CAkey need use CA's private key, here i am CA so use server.key
openssl x509 -req -days 365 -in server.csr -CA ca.crt -CAkey server.key -CAcreateserial -out server.crt

