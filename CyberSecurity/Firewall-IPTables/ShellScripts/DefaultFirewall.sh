#!/usr/bin/bash

echo "Cleaning the Firewall"
iptables -F
iptables -t nat -F
iptables -t mangle -F

echo "Setting Up Firewall Policies"
iptables -P INPUT ACCEPT 
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE
