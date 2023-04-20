# Aula: Comandos para instalar e configurar o https e ver ideia de host virtual.

# Atualizar os pacotes do sistema - SERVER.
apt update -y

# Instalar o apache - SERVER.
apt install apache2 -y

# Inicializar o apache - SERVER.
apachectl start

#Verificar se ligou. Se ligou corretamente, irá mostrar executando tcp6 na porta 80 - SERVER.
netstat -a --tcp -n

# Arquivo consiste em uma tabela para mapear os nomes -> tipo um DNS... - HOST1
# Neste arquivo dizemos qual ip cuida de qual domínio (exemplo: 192.168.122.100 www.google.com.br)
vi /etc/hosts

# Adicionar no fim do arquivo:
192.168.122.100 www.dominio1.com
192.168.122.100 www.dominio2.com
192.168.122.100 www.utfpr.edu.br

# Adicionando conteúdo em cada um dos sites - SERVER.
echo "bem vindo ao site" > /var/www/html/index.html
echo "bem vindo ao dominio 1" > /var/www/html/dominio1/index.html
echo "bem vindo ao dominio 2" > /var/www/html/dominio2/index.html
echo "bem vindo a utfpr" > /var/www/html/utfpr/index.html

# Abrir o arquivo com o virtualhost do site- SERVER
vi /etc/apache2/sites-available/dominio1.conf

# Adicionar isso no arquivo:
<VirtualHost *:80>
        ServerName www.dominio1.com
        DocumentRoot /var/www/html/dominio1
</VirtualHost>

# Salve o arquivo com esc esc : wq e depois digite
cp /etc/apache2/sites-available/dominio1.conf /etc/apache2/sites-available/dominio2.conf
cp /etc/apache2/sites-available/dominio1.conf /etc/apache2/sites-available/utfpr.conf

# Editar o dominio2
vi /etc/apache2/sites-available/dominio2.conf
<VirtualHost *:80>
        ServerName www.dominio2.com
        DocumentRoot /var/www/html/dominio2
</VirtualHost>

#Editar o utfpr
vi /etc/apache2/sites-available/utfpr.conf
<VirtualHost *:80>
        ServerName www.utfpr.edu.br
        DocumentRoot /var/www/html/utfpr
</VirtualHost>

#Voltando no terminal do server
ln -s /etc/apache2/sites-available/dominio1 /etc/apache2/sites-enabled
ln -s /etc/apache2/sites-available/dominio2 /etc/apache2/sites-enabled
ln -s /etc/apache2/sites-available/utfpr /etc/apache2/sites-enabled

# Ver se o site está enabled:
ls -l /etc/apache2/sites-enabled/

# Reinicar o apache
apachectl stop
apachectl start

#Verificar se o apache reiniciou corretamente.
netstat -a --tcp -n

# - SERVER
a2enmod ssl
apachectl stop
apachectl start
make-ssl-cert generate-default-snakeoil --force-overwrite
apt install dialog -y
make-ssl-cert generate-default-snakeoil --force-overwrite
a2ensite default-ssl
apachectl stop
apachectl start

# Agora devia estar rodando tanto o http quanto o https
netstat -a --tcp 

# Editar o arquivo da utfpr para redirecionar o dominio http para https
vi /etc/apache2/sites-available/utfpr.conf

# O conteúdo do arquivo deve ficar da seguinte forma:
<VirtualHost *:80>
        ServerName www.utfpr.edu.br
        DocumentRoot /var/www/html/utfpr
        Redirect / https://www.utfpr.edu.br
</VirtualHost>

<VirtualHost *:443>
        ServerName www.utfpr.edu.br
        DocumentRoot /var/www/html/utfpr
</VirtualHost>

# Reinicie o apache:
apachectl stop && apachectl start
netstat -a --tcp 