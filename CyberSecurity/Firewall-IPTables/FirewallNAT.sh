#!/usr/bin/bash

echo "Cleaning the Firewall Rules"

iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies as DROP Everything"
iptables -P INPUT DROP
iptables -P OUTPUT DROP
iptables -P FORWARD DROP

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "Redirect to Host3 HTTP Port"
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 8080 -j DNAT --to 10.2.0.3:80

echo "Redirect HTTP to the HOST4"
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 80 -j DNAT --to 10.2.0.4

echo "Redirect HTTP from Network 10.1.0.0 to the Firewall itself"
iptables -t nat -A PREROUTING -i eth1 -p tcp --dport 80 -j REDIRECT

echo "Filtering Rules"
iptables -A FORWARD -i eth2 -o eth0 -p tcp --dport 80 -d 10.2.0.3 -j ACCEPT
iptables -A FORWARD -p tcp --dport 80 -s 10.2.0.3 -j ACCEPT
