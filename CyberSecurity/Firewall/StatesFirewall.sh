#!/usr/bin/bash
echo "Cleaning Tables"
iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies"
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "LAN 10.1.0.0 Screened"
iptables -A FORWARD -o eth1 -d 10.1.0.0/24 -m state --state NEW,INVALID -j DROP

echo "Host 3 Server HTTP Only"
iptables -A FORWARD -d 10.2.0.3/24 -p tcp ! --dport 80 -m state --state NEW,INVALID -j DROP

echo "Host 4 Server HTTP and HTTPS Only"
iptables -A FORWARD -d 10.2.0.4 -p tcp --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.2.0.4 -p tcp --dport 443 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.2.0.4 -m state --state NEW,INVALID -j DROP
