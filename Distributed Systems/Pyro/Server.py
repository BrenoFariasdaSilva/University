import Pyro5.api as pyro
from Contacts import Contacts

daemon = pyro.Daemon() # executa o Daemon do Pyro5
ns = pyro.locate_ns() # localiza o servidor de nomes
uri = daemon.register(Contacts) # registra os Contatos como um objeto Pyro
ns.register("ContactsService", uri) # registra o objeto com  um servidor de nomes

print("Objeto Contacts registrado.")
daemon.requestLoop()                     # servidor aguardando solicitações
