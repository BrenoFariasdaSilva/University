#!/usr/bin/bash

echo "Cleaning Tables"
iptables -F # Clean the Filter Table
iptables -t nat -F # Clean the NAT Table
iptables -t mangle -F # Clean the Mangle Table

echo "Setting Up Firewall Policies"
# 01 - Utilizar o política de bloquear tudo em todas as situações;
iptables -P INPUT DROP
iptables -P OUTPUT DROP
iptables -P FORWARD DROP

echo "NAT Rules"
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "LAN 1 Screened"
# 02 - A LAN1 deve ser uma LAN screened;
iptables -A FORWARD -s 10.1.0.0/24 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.1.0.0/24 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "HOST 3 Server HTTP/HTTPS"
# 03 - O Host C deve ser acessado via HTTP/HTTPS de qualquer rede, inclusive da Internet;
iptables -A FORWARD -d 10.2.0.3 -p tcp --dport 80 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.2.0.3 -p tcp --dport 443 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -s 10.2.0.3 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "HOST 4 Can be Accessed via DNS (Internet included)"
# 04 - O Host D deve ser acessado via DNS de qualquer rede, inclusive da Internet;
iptables -A FORWARD -d 10.2.0.4 -p udp --dport 53 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -s 10.2.0.4 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "LAN1 Can Access HOST 3 and 4 by SSH"
# 05 - Somente o LAN1 pode acessar os Hosts C e D via SSH – outros hosts não podem;
iptables -A FORWARD -s 10.1.0.0/24 -d 10.2.0.0/24 -p tcp --dport 22 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -d 10.1.0.0/24 -s 10.2.0.0/24 -p tcp --sport 22 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "Only HOST 1 Can Access Firewall by SSH using MAC and IFace"
# 06 - Somente o Host A pode acessar o Firewall via SSH, isso deve ser controlado por MAC e placa de rede;
iptables -A INPUT -s 10.1.0.1 -p tcp --dport 22 -i eth1 -m state --state NEW,ESTABLISHED,RELATED -m mac --mac-source 00:00:00:00:00:01 -j ACCEPT
iptables -A OUTPUT -d 10.1.0.1 -p tcp --sport 22 -o eth1 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "Firewall is a HTTP HTTPS and DNS Client from Internet"
# 07 - O Firewall pode acessar como cliente, os serviços de HTTP, HTTPS e DNS da Internet.
iptables -A OUTPUT -p tcp --dport 80 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A INPUT -p tcp --sport 80 -i eth2 -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A OUTPUT -p tcp --dport 443 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A INPUT -p tcp --sport 443 -i eth2 -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A OUTPUT -p udp --dport 53 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A INPUT -p tcp --sport 53 -i eth2 -m state --state ESTABLISHED,RELATED -j ACCEPT

echo "Firewall is a Gateway VPN"
# 08 - O Firewall deve ser um Gateway VPN, utilizando o OpenVPN, e isso deve ser liberado via Firewall
# O host E deve ter acesso total aos hosts da LAN1 e LAN2 via VPN.

# Server:
# # Server
# # Install OpenVPN
# dev tun
# ifconfig 10.8.0.254 10.8.0.5 # Ifconfig IPServer IPHost
# secret static.key

# Client:
# remote IPPúblicoGatewayVPNHere
# dev tun
# ifconfig 10.8.0.5 10.8.0.254 # Ifconfig IPHost IPServer
# # Now generate a file named static.key with the content of the static.key of the server
# secret static.key
# route 10.1.0.0 255.255.255.0
# route 10.2.0.0 255.255.255.0

# Rota do HOST E para o Firewall
iptables -A INPUT -s 192.168.122.5 -i eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A OUTPUT -d 192.168.122.5 -o eth2 -m state --state NEW,ESTABLISHED,RELATED -j ACCEPT
iptables -A INPUT -s 10.8.0.5 -i eth2 -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A OUTPUT -d 10.8.0.5 -o eth2 -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -i tun -j ACCEPT

# 09 - O Firewall também deve ter um Proxy Squid instalado e configurado para ser utilizado pelos hosts da LAN1.
# Sendo assim, os hosts da LAN1 devem obrigatoriamente utilizar o proxy para acessar HTTP nas outras redes.
# (Bloqueie o roteamento das portas HTTP e HTTPS da LAN1 para outras redes – o acesso só é permitido via Proxy)

# apt update -y
# apt install squid -y
# systemctl is-enabled squid
# vi /etc/squid/squid.conf
# "/http_port 3128"
# http_port 10.1.0.254:3128
# "/include /etc/squid/conf.d/*.conf"
# acl mynet src 10.1.0.0/24
# http_access allow mynet

iptables -A INPUT -s 10.1.0.0/24 -i eth1 -p tcp --dport 3128 -j ACCEPT
iptables -A OUTPUT -d 10.1.0.0/24 -o eth1 -p tcp --sport 3128 -j ACCEPT
iptables -A FORWARD -s 10.1.0.0/24 -i eth1 -p tcp --dport 80 -j DROP
iptables -A FORWARD -s 10.1.0.0/24 -i eth1 -p tcp --dport 443 -j DROP
