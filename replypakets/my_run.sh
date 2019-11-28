#!/bin/sh
#tcpreplay -i enp2s0 --pps 1 --limit=1000 big.pcap 
#            interface      number of packtes to send
#                   packets per second   packet name
while true; do
	#these tow gre packet
	#tcpreplay -i enp2s0 --pps 1 --limit=1000 big.pcap 
	#tcpreplay -i enp2s0  --limit=1000 nsfocus.pcap 

	# 
	#tcpreplay -i enp2s0  --limit=1000 huannan_fuxian.pcap

	# a http stream
	tcpreplay-edit --enet-dmac=88:df:9e:67:35:ea -i enp2s0  --limit=1000 http.pcap
	sleep 1
done
