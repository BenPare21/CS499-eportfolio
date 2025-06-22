package com.example;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Date;

public class AppointmentServiceTest {
	private AppointmentService service;
	private Appointment appointment1;
	private Appointment appointment2;
	
	
	@BeforeEach
	public void setUp() {
		service = new AppointmentService();
		appointment1 = new Appointment("1234567890", new Date(System.currentTimeMillis()+10000),"Test Description 1");
		appointment2 = new Appointment("0987654321", new Date(System.currentTimeMillis()+20000),"Test Description 2");
	}
	
	@Test
	public void testAddAppointment() {
		assertTrue(service.addAppointment(appointment1));
		assertTrue(service.addAppointment(appointment2));
		assertFalse(service.addAppointment(appointment1));//duplicate ID
	}
	
	@Test
	public void testDeleteAppointment() {
		service.addAppointment(appointment1);
		assertTrue(service.deleteAppointment("1234567890"));
		assertFalse(service.deleteAppointment("1234567890"));
	}
	
	@Test 
	public void testGetAppointment() {
		service.addAppointment(appointment1);
		Appointment retrieved = service.getAppointment("1234567890");
		assertNotNull(retrieved);
		assertEquals("1234567890", retrieved.getAppointmentID());
		assertEquals(appointment1.getAppointmentDate(), retrieved.getAppointmentDate());
		assertEquals("Test Description 1", retrieved.getDescription());
	}
	
	@Test
	//Test for updating appointment date, method added in response to feedback
	public void testUpdateAppointmentDate() {
		service.addAppointment(appointment1);
		Date newDate = new Date(System.currentTimeMillis() + 30000);
		
		assertTrue(service.updateAppointmentDate("1234567890", newDate));
		assertEquals(newDate, service.getAppointment("1234567890").getAppointmentDate());
	}
	
	
	@Test
	//Test for updating appointment description method added in response to feedback
	public void testUpdateAppointmentDescription() {
		service.addAppointment(appointment1);
		String newDescription = "Updated Description";
		
		assertTrue(service.updateAppointmentDescription("1234567890", newDescription));
		assertEquals(newDescription, service.getAppointment("1234567890").getDescription());
	}

	
	
}
