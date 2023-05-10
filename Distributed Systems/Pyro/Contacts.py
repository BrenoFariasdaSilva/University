import Pyro5.api as pyro

@pyro.behavior(instance_mode="session")
@pyro.expose
class Contacts:
    contacts_dictionary = {}
    
    def add(self, new_contact, contact_number):
        self.contacts_dictionary[new_contact] = contact_number
        return f"Contact {new_contact} added with number {contact_number}"
    
    def deleteByContactName(self, contact_name):
        if self.contacts_dictionary[contact_name] != None:
            self.contacts_dictionary.pop(contact_name)
            return f"Contact {contact_name} removed"
        return "Contact not found"
    
    def get(self, contact_name):
        if self.contacts_dictionary[contact_name] != None:
            return self.contacts_dictionary[contact_name]
        return "Contact not found"
        
    def contacts_ordered(self):
        return sorted(self.contacts_dictionary)