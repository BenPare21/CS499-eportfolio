package contactServiceBen_P;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;


public class ContactServiceTest {



    private ContactService contactService;

    @BeforeEach
    public void setUp() {
        contactService = new ContactService();
    }

    @Test
    public void testAddContact() {
        Contact contact = new Contact("1");
        contact.setFirstName("Ben");
        contact.setLastName("Pare");
        contact.setPhoneNumber("6032345123");
        contact.setAddress("123 Dirt Rd");

        assertTrue(contactService.addContact(contact));
        assertFalse(contactService.addContact(contact));
    }

    @Test
    public void testUpdateContact() {
        Contact contact = new Contact("1");
        contactService.addContact(contact);

        assertTrue(contactService.updateContact("1", "Ben", "Pare", "1111111111", "123 Dirt Road"));
        assertEquals("Ben", contactService.getContact("1").getFirstName());
        assertEquals("Pare", contactService.getContact("1").getLastName());
        assertEquals("1111111111", contactService.getContact("1").getPhoneNumber());
        assertEquals("123 Dirt Road", contactService.getContact("1").getAddress());

        assertFalse(contactService.updateContact("2", "Ben", "Pare", "111111111", "333333333"));
    }

    @Test
    public void testDeleteContact() {
        Contact contact = new Contact("1");
        contactService.addContact(contact);

        assertTrue(contactService.deleteContact("1"));
        assertFalse(contactService.deleteContact("1"));
    }

    @Test
    public void testGetContact() {
        Contact contact = new Contact("1");
        contactService.addContact(contact);

        assertNotNull(contactService.getContact("1"));
        assertNull(contactService.getContact("2"));
    }

	
	
}
