#!/usr/bin/bash

echo "Cleaning the Firewall"
iptables -F
iptables -t nat -F
iptables -t mangle -F

echo "Setting Policies"
# 01 - Utilizar o política de liberar tudo em todas as situações, exceto na INPUT, que deve ser DROP;
iptables -P INPUT DROP
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT

echo "NAT Rules"
# 02- A LAN1 deve ser uma LAN screened
# Nat faz isso, mas para as duas LANs.
iptables -t nat -A POSTROUTING -o eth2 -j MASQUERADE

echo "Allow Host C be Accessed via HTTP/HTTPS from WANs"
# 03 - O Host C deve ser acessado via HTTP/HTTPS de qualquer rede, inclusive da Internet;
# A saída não precisa ser alterada, pois o NAT já faz isso, basta redirecionar o pacote que chegou.
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 80 -j DNAT --to 10.2.0.3
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 443 -j DNAT --to 10.2.0.3

echo "Allow Host D Be Accessed via DNS, SMTP and POP3 from WANs"
# 04 - O Host D deve ser acessado via DNS, SMTP e POP3 de qualquer rede, inclusive da Internet;
# A saída não precisa ser alterada, pois o NAT já faz isso, basta redirecionar o pacote que chegou.
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 53 -j DNAT --to 10.2.0.4
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 587 -j DNAT --to 10.2.0.4
iptables -t nat -A PREROUTING -i eth2 -p tcp --dport 110 -j DNAT --to 10.2.0.4

echo "Block any Access to Host C and D via SSH, except from LAN1"
# 05 - Somente o LAN1 pode acessar os Hosts C e D via SSH – outros hosts não podem;
# Bloquear qualquer tentativa de conexão SSH para o host C e D, a não ser que a origem seja da rede 10.1.0.0/24
iptables -A FORWARD -p tcp --dport 22 -s !10.1.0.0/24 -d 10.2.0.3 -j DROP
iptables -A FORWARD -p tcp --dport 22 -s !10.1.0.0/24 -d 10.2.0.4 -j DROP

echo "Block any SSH Access to Firewall, except from Host A"
# 06 - Somente o Host A pode acessar o Firewall via SSH;
# Não é necessário Output, pois já está com ACCEPT.
iptables -A INPUT -s !10.1.0.1 -p tcp --dport 22 -j DROP

echo "Firewall Can Access HTTP, HTTPS and DNS from Internet as a Client"
# 07 - O Firewall pode acessar como cliente, os serviços de HTTP, HTTPS e DNS da Internet;
# Não é necessário Output, pois já está com ACCEPT.
iptables -A INPUT -i eth2 -p tcp --sport 22 -j ACCEPT 
iptables -A INPUT -i eth2 -p tcp --sport 80 -j ACCEPT 
iptables -A INPUT -i eth2 -p tcp --sport 443 -j ACCEPT 

echo "No one can access Telnet"
# 08 - Ninguém pode acessar Telnet entre as redes.
# Não precisa configurar output, pois já está bloqueado.
iptables -A FORWARD -p tcp --dport 23 -j DROP
iptables -A OUTPUT -p tcp --dport 23 -j DROP

echo "Only Allow LAN1 and LAN2 Access DNS from 8.8.8.8"
# 09 - Todos os hosts da LAN1 e LAN2 devem obrigatoriamente utilizar o 8.8.8.8 como servidor DNS.
iptables -A FORWARD -p tcp --sport 53 ! -d 8.8.8.8 -j DROP # Block DNS from other servers
iptables -t nat -A PREROUTING -p tcp --sport 53 -j DNAT --to 8.8.8.8 # Redirect DNS from other IPs to 8.8.8.8
