#!/usr/bin/bash

echo "Cleaning the Firewall Rules"
iptables -F
iptables -t nat -F
iptables -t mangle -F

echo "Setting Up Firewall Policies as DROP Everything"
iptables -P INPUT DROP
iptables -P OUTPUT DROP
iptables -P FORWARD DROP

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "Allow HTTP"
iptables -A FORWARD -p tcp --dport 80 -j ACCEPT
iptables -A FORWARD -p tcp --sport 80 -j ACCEPT

echo "Allow HTTP"
iptables -A FORWARD -p tcp --dport 443 -j ACCEPT
iptables -A FORWARD -p tcp --sport 443 -j ACCEPT

echo "Allow DNS"
iptables -A FORWARD -p udp --dport 53 -j ACCEPT
iptables -A FORWARD -p udp --sport 53 -j ACCEPT

echo "Network 10.1.0.0 Access Firewall via SSH"
iptables -A INPUT -i eth1 -p tcp --dport 22 -j ACCEPT
iptables -A OUTPUT -p tcp --sport 22 -j ACCEPT
