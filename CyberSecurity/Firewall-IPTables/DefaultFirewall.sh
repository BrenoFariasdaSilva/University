#!/usr/bin/bash

echo "Cleaning the Firewall Rules"
iptables -F
iptables -t nat -F
iptables -t mangle -F

echo "Setting Up Firewall Policies as ACCEPT Everything"
iptables -P INPUT ACCEPT 
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
echo "Enable NAT Masquerade For Packets Leaving From The eth2 Network Interface"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE
