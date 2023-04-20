apt update -y
apt install samba -y

cp /etc/samba/smb.conf /etc/samba/smb.conf-default
vi /etc/samba/smb.conf 

# Depois editar a linha 175 do arquivo e deixe da seguinte forma:
[homes]
   comment = Home Directories
   browseable = no
   writable = yes
# Saia e salve

# Inicie o processos com os comandos:
/etc/init.d/smbd start
/etc/init.d/nmbd start

# Verifique se o serviço está funcionando
netstat -a --udp -n

# adicione um user
adduser user1 
# Use a senha 123mudar

# No gerenciador de arquivos use o control + l e digite:
No Linux: smb://user1@192.168.122.102
No Windows: 192.168.122.102

# Você precisa ter uma senha no smbpasswd
smbpasswd -a user1
# Use uma senha diferente da senha do usuário

# Abra novamente o arquivo de configurações do servidor samba
vi /etc/samba/smb.conf 
# E adicione no fim do arquivo:
[temp]
        comment = dir temporario ; Comentario do compartilhamento.
        path = /tmp ; Qual diretorio esta compartilhando.
        writable = no ; Se eh alteravel.
        browseable = yes ; Se eh visivel na listagem dos arquivos.
        public = yes ; Se eh publico
        guest ok = yes ; Se qualquer um pode acessar, mesmo nao usando o SAMBA
# Saia e salve
testparm /etc/samba/smb.conf

# Criar grupo e mudar o owner do arquivo
addgroup empresa
chown user1.empresa /mnt/empresa/

# Dar todas as permissões para o dono, r e x para o grupo e nada para outros (rwx -> 4 2 1)
chmod 750 /mnt/empresa/
# Ou
chmod o -rx 
# Ou
chmod o=rx
# Ou
chmod a+x

# Se der problema com a senha no login, mude a senha
smbpasswd -a user1

vi /etc/group

chgrp vendas /mnt/empresa/vendas
chgrp rh /mnt/empresa/RH/

vi /etc/samba/smb.conf 

[vendas]
        comment = vendas
        path = /mnt/empresa/vendas
        browseable = yes
        valid users = @vendas
        writable = yes


[rh]
        comment = RH
        path = /mnt/empresa/RH
        browseable = yes
        valid users = @rh
        writable = yes

testparm /etc/samba/smb.conf