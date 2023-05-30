## Como executar:
É necessário instalar primeiramento o RabbitMQ.
Segue link: 

### Excutando client.py 
Para executar o client.py é preciso passar os parâmetros dos tópicos:
```
python client.py people alone beautiful 
```
### Executando classificador:
```
python classificador.py
```
### Executando coletor:
```
python coletor.py
```
## Bibliotecas usadas:   
- tweepy: Implementa uma interface para acessar o Twitter.
- pika: Implementa o protocolo AMQP 0-9-1.

## Exemplos de uso: 
Existem 7 possíveis fila que o cliente pode se inscrever: "people", "beautiful", "actor", "Fasting", "innovation", "lesson", "alone".

No primeiro terminal execute o client.py, passando os parametros desejados: 
```
python client.py people
```
No segundo terminal execute o classificador:
```
python classificador.py
```
No terceiro, e último, terminal execute o coletor:
```
python coletor.py
```
Todos os terminais devem estar sendo executados ao mesmo tempo.

No console do terminal do client irá aparecer os tweets que estão relacionados com os tópidos da fila escolhido. Segue exemplo:
```
Tópico: 'people'
UserName: Beth S. Linas, PhD, MHS (she/her)
Tweet: For those that can- try &amp; limit unnecessary trips/outings where youâ€™re around people. IE: limit unnecessary shoppinâ€¦ https://t.co/R2D6c9WPt2
```