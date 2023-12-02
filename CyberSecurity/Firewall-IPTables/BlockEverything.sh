#!/usr/bin/bash

echo "Cleaning the Firewall Rules"
iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies as DROP Everything"
iptables -P INPUT DROP # DROP Policy in the INPUT Chain
iptables -P OUTPUT DROP # DROP Policy in the OUTPUT Chain
iptables -P FORWARD DROP # DROP Policy in the FORWARD Chain

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE # NAT Rules

echo "Allow HTTP"
iptables -A FORWARD -p tcp --dport 80 -j ACCEPT # Allow HTTP Request
iptables -A FORWARD -p tcp --sport 80 -j ACCEPT # Allow HTTP Response

echo "Allow HTTP"
iptables -A FORWARD -p tcp --dport 443 -j ACCEPT # Allow HTTPS Request
iptables -A FORWARD -p tcp --sport 443 -j ACCEPT # Allow HTTPS Response

echo "Allow DNS"
iptables -A FORWARD -p udp --dport 53 -j ACCEPT # Allow DNS Request
iptables -A FORWARD -p udp --sport 53 -j ACCEPT # Allow DNS Response

echo "Network 10.1.0.0 Access Firewall via SSH"
iptables -A INPUT -i eth1 -p tcp --dport 22 -j ACCEPT # Allow SSH Request
iptables -A OUTPUT -p tcp --sport 22 -j ACCEPT # Allow SSH Response
