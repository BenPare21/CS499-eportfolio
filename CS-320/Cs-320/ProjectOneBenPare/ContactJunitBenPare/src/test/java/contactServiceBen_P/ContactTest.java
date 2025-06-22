package contactServiceBen_P;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;


public class ContactTest {

	@Test
	public void testContactConstructor() {
		Contact contact = new Contact("123");
		assertEquals("123", contact.getContactId(), "Contact Id did not match the expected value");
		assertNull(contact.getFirstName() ,"First name should be null initially");
		assertNull(contact.getLastName(), "Last name should be null initially");
		assertNull(contact.getPhoneNumber(), "Phone number should not be null initially");
		assertNull(contact.getAddress(), "Address should not be null intially");
	}
	
	@Test
	public void testSetAndGetFirstName() {
		Contact contact = new Contact("123");
		contact.setFirstName("Ben");
		assertEquals("Ben", contact.getFirstName(),"First name did not match the expected value");
	}
	
	@Test
	public void setAndGetLastName() {
		Contact contact = new Contact("123");
		contact.setLastName("Pare");
		assertEquals("Pare", contact.getLastName(),"Last name did not match the expected value");
	}
	
	@Test
	public void testSetAndGetPhoneNumber() {
		Contact contact = new Contact("123");
		contact.setPhoneNumber("1603324351");
		assertEquals("1603324351",contact.getPhoneNumber(),"Phone number did not match the excpected value");
		}
	
	@Test
	public void testSetAndGetAddress() {
		Contact contact = new Contact("123");
		contact.setAddress("123 Dirt Rd");
		assertEquals("123 Dirt Rd", contact.getAddress(),"Address did not match the expected value");
	}
	
}
