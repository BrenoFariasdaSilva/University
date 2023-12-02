#!/usr/bin/bash

echo "Cleaning the Firewall Rules"
iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies as ACCEPT Everything"
iptables -P INPUT ACCEPT 
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
echo "Enable NAT Masquerade For Packets Leaving From The eth2 Network Interface"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE
