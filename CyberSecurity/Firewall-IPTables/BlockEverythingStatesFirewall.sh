#!/usr/bin/bash
echo "Cleaning Tables"
iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies"

iptables -P INPUT DROP
iptables -P OUTPUT DROP
iptables -P FORWARD DROP

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "LAN 1 Screened"
iptables -A FORWARD -s 10.1.0.0/24 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.1.0.0/24 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "HOST 3 Server HTTP"
iptables -A FORWARD -d 10.2.0.3 -p tcp --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -s 10.2.0.3 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "HOST 4 HTTP and HTTPS Server Only" 
iptables -A FORWARD -d 10.2.0.4 -p tcp --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.2.0.4 -p tcp --dport 443 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -s 10.2.0.4 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "HOST 1 Can Access Firewall by SSH controlled by MAC Address"
iptables -A INPUT -p tcp --dport 22 -m mac --mac-source fe:61:6b:46:da:a0 -j ACCEPT
iptables -A OUTPUT -p tcp --sport 22 -j ACCEPT

echo "Ping Firewall 4 Times"
iptables -A INPUT -p icmp --icmp-type echo-request -m limit --limit-burst 4 -j ACCEPT
iptables -A OUTPUT -p icmp -j ACCEPT
