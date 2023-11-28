#!/usr/bin/bash

echo "Cleaning Tables"
iptables -F
iptables -t nat -F
iptables -t mangle -F

echo "Setting Up Firewall Policies"
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "Filtering Rules"
echo "Blocking any FORWARD Telnet Package" 
iptables -A FORWARD -p tcp --dport 23 -j DROP

echo "Blocking FORWARD TCP HTTP Packages from 10.1.0.1 to 10.2.0.3"
iptables -A FORWARD -s 10.1.0.1 -d 10.2.0.3 -p tcp --dport 80 -j DROP

echo "Blocking any INPUT Telnet Package"
iptables -A INPUT -p tcp --dport 23 -j DROP

echo "Blocking any OUTPUT Telnel Package"
iptables -A OUTPUT -p tcp --dport 23 -j DROP
