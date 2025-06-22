package contactServiceBen_P;

public class Contact {

	// Final means this variable does not change
		private final String contactId;
		
		//constructor
		public Contact(String contactId) {
			
			if(contactId == null || contactId.length()>10) {
				throw new IllegalArgumentException("Contact ID cannot be null and must be 10 characters or less.");
			}
			
			this.contactId = contactId;
		}
		
		//These variables can change over time
	    private String firstName;
	    private String lastName;
	    private String phoneNumber; //renamed for clarity
	    private String address; //renamed cause all other variables lowercase
	    // Since this data is sensitive we use private

	    
	    //Since contactId is not made by user we do not need a getter
	   
	    //Initializing the variables
	    //Getter 
	    //Getters allow access to private variables
	  
	    public String getContactId() {
	    	return contactId;
	    }
	    
	    
	    
	    public String getFirstName() {
	    	return firstName;
	    }
	    //setter
	    //setters allow changes to private variables
	    public void setFirstName(String firstName) {
	    	if(firstName == null||firstName.length()>10) {
	    		throw new IllegalArgumentException("First name cannot be null and must be 10 characters or less");
	    	}
	    	this.firstName = firstName; 
	    }
	    
	    // Getters and setters have big O(1) linear typically.
	    // Getters and setters use Encapsulation where other methods do direct acess
	    // Encapsulation allows data to be protected more.

	    public String getLastName() {
	    	return lastName;
	    }
	    //gets passed lastName
	    public void setLastName(String lastName) {
	    	if(lastName == null || lastName.length()>10) {
	    		throw new IllegalArgumentException("Last name cannot be null and must be 10 characters or less");
	    	}
	    	
	    	this.lastName = lastName;
	    }
	    
	    public String getPhoneNumber() {
	    	return phoneNumber;
	    }
	    public void setPhoneNumber(String phoneNumber) {
	    	if(phoneNumber == null || !phoneNumber.matches("\\d{10}")) {
	    	throw new IllegalArgumentException("Phone number must be exactly 10 digits.");	
	    	}
	    	this.phoneNumber = phoneNumber;
	    }
	    
	    public String getAddress() {
	    	return address;
	    }
	    public void setAddress(String address) {
	    	if(address == null || address.length() > 30) {
	    		throw new IllegalArgumentException("Address cannot be null and must be 30 characters or less.");
	    	}
	    	this.address = address;
	    }

	
}
