#!/usr/bin/bash

# 1 - Listar as regras anexadas ao iptables nas tabelas: filters; nat; mangle. E também observar as políticas das chains (situações).
iptables -L

# 2 - Configurar o alvo padrão das chains referente a tabela filter como DROP.
iptables -P INPUT DROP
iptables -P FORWARD DROP
iptables -P OUTPUT DROP

# 3 - Liberar totalmente o trafego de entrada de nossa interface de loopback (lo).
# Essa regra deve sempre fazer parte do script de inicialização para permitir a comunicação entre processos locais.
# Lembre-se está regra não é opcional se você estiver usando políticas de negar tudo (DROP) o que não for permitido.
iptables -A INPUT -l lo -j ACCEPT

# 4 - Proibir qualquer pacote oriundo de nossa LAN (10.0.30.0) endereçados ao site www.terra.com.br.
iptables -A FORWARD -s 10.0.30.0/8 -d www.terra.com.br -j DROP

# 5 - Especificar que qualquer pacote oriundo do host www.cracker.com não pode penetrar em nossa rede (10.0.30.0).
iptables -A FORWARD -s www.cracker.com -d 10.0.30.0/8 -j DROP

# 6 - Faremos agora com que os pacotes provenientes do site da universidade www.universidade.br penetrem livremente em nossa rede.
iptables -A FORWARD -s www.universidade.br -d 10.0.30.0/8 -j ACCEPT

# 7 - Todos os pacotes oriundos de qualquer rede que penetre em nosso Firewall pela interface eth2 serão redirecionados para o computador 10.0.30.47.
iptables -t nat -A PREROUTING -i eth2 -j DNAT --to 10.0.30.47

# 8 - Fazer com que qualquer pacote que deseje sair da rede local para outra rede possua seu endereço de origem alterado para 192.168.0.33,
# implementando assim o conceito de máscaramento IP. Este mesmo pacote somente sofrerá modificações se sair pela interface de rede eth2.
iptables -t nat -A POSTROUTING -o eth2 -j SNAT --to 192.168.0.33

# 9 - Utilizar a tabela filter para rejeitar pacotes entrantes pela interface de rede eth1.
iptables -A FORWARD  -i eth1 -j REJECT

# 10 - Todos os pacotes que entram por qualquer interface de rede com exceção da eth0 sejam descartados.
iptables -A FORWARD -i ! eth0 -j DROP

# 11 - Deletar a segunda regra inserida sobre a chain FORWARD.
iptables -D FORWARD 2

# 12 - Listar agora as regras associadas a chain OUTPUT.
iptables -L OUTPUT

# 13 - Descartar qualquer pacote oriundo do IP 10.0.80.32 destinado ao IP 10.0.30.4.
iptables -A FORWARD -s 10.0.80.32/8 -d 10.0.30.4 -j DROP

# 14 - Pacotes TCP destinados à porta 80 de nosso host firewall deverão ser descartados.
iptables -A INPUT -p tcp --dport 80 -j DROP

# 15 - Fazer com que pacotes destinados a porta 25 de nosso host Firewall sejam arquivados em log e em seguida sejam descartados.
iptables -A INPUT -p tcp --dport 25 -j REJECT
