import Pyro5.api as pyro

def main():
    ## pyro.locate_ns("127.0.0.1", 9090)
    ## contacts = pyro.Proxy("PYRONAME:contactsService")
    nameserver = pyro.locate_ns()
    uri = nameserver.lookup("ContactsService")
    contacts = pyro.Proxy(uri)
    
    print(contacts.add("Breno", "123456789"))
    print(contacts.add("Campiolo", "987654321"))
    print(contacts.add("Test", "000000000"))
    print(contacts.deleteByContactName("Test"))
    print(contacts.get("Breno"))
    print(contacts.contacts_ordered())

if __name__ == "__main__":
    main()