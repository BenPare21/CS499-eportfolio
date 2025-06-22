package com.example;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import java.util.Date;

public class AppointmentTest {

    @Test
    public void testValidAppointment() {
        Date futureDate = new Date(System.currentTimeMillis() + 10000); // 10 seconds in the future
        Appointment appointment = new Appointment("1234567890", futureDate, "Test Description");
        assertEquals("1234567890", appointment.getAppointmentID());
        assertEquals(futureDate, appointment.getAppointmentDate());
        assertEquals("Test Description", appointment.getDescription());
    }

    @Test
    public void testInvalidAppointmentID() {
        Date futureDate = new Date(System.currentTimeMillis() + 10000); // 10 seconds in the future
        
        // Test null ID
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment(null, futureDate, "Test Description");
        });
        //Test ID too long
        assertThrows(IllegalArgumentException.class, () ->{
        	new Appointment("12345678901", futureDate, "Test Description");
        });
    }
    
    @Test
    //Testing setter for appointmentDate, added in response to feedback
    public void testSetAppointmentDate() {
    	Date futureDate = new Date(System.currentTimeMillis() + 10000 );
    	Date newDate = new Date(System.currentTimeMillis() + 20000);
    	Appointment appointment = new Appointment("1234567890", futureDate, "Test Description");
    	
    	appointment.setAppointmentDate(newDate);
    	assertEquals(newDate, appointment.getAppointmentDate());
    }
    
    @Test
    //Testing setter for description, added in response to feedback
    public void testSetDescription() {
    	Date futureDate = new Date(System.currentTimeMillis()+ 10000);
    	Appointment appointment = new Appointment("1234567890", futureDate, "Test Description");
    	String newDescription = "Updated Description";
    	
    	appointment.setDescription(newDescription);
    	assertEquals(newDescription, appointment.getDescription());
    }
    
    
    
    

    @Test
    public void testInvalidAppointmentDate() {
        Date pastDate = new Date(System.currentTimeMillis() - 10000); // 10 seconds in the past
        
        // Test null date
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("1234567890", null, "Test Description");
        });

        // Test date in the past
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("1234567890", pastDate, "Test Description");
        });
    }

    @Test
    public void testInvalidDescription() {
        Date futureDate = new Date(System.currentTimeMillis() + 10000); // 10 seconds in the future

        // Test null description
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("1234567890", futureDate, null);
        });

        // Test description too long
        assertThrows(IllegalArgumentException.class, () -> {
            new Appointment("1234567890", futureDate, "This description is way too long and exceeds the fifty character limit.");
        });
    }
}
