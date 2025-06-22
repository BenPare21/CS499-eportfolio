package contactServiceBen_P;

import java.util.HashMap;
import java.util.Map;


public class ContactService {

	private Map<String, Contact> contacts;
	
	public ContactService() {
		contacts = new HashMap<>();
	}
	
	public boolean addContact(Contact contact)
	{
		if(contacts.containsKey(contact.getContactId())) {
			return false;
		}
	contacts.put(contact.getContactId(),contact);
	return true;
	}
	
	public boolean updateContact(String contactId, String firstName, String lastName, String phoneNumber, String address) {
		Contact contact = contacts.get(contactId);
		if(contact == null) {
			return false;
		}
		if(firstName != null) contact.setFirstName(firstName);
		if(lastName != null) contact.setLastName(lastName);
		if(phoneNumber != null) contact.setPhoneNumber(phoneNumber);
		if(address != null) contact.setAddress(address);
		return true;
	}
	
	public boolean deleteContact(String contactId) {
		if(contacts.remove(contactId) == null){
			return false;
		}
		return true;
	}
	
	public Contact getContact(String contactId) {
		return contacts.get(contactId);
	}

	
}
