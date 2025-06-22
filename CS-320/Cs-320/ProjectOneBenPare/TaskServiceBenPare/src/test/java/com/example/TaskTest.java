package com.example;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class TaskTest {

	@Test
	public void testTaskCreationValidData() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		assertEquals("1",task.getTaskId());
		assertEquals("Test Task", task.getName());
		assertEquals("This is a test task.", task.getDescription());
	}
	
	@Test
	public void testTaskCreationInvalidTaskId() {
		assertThrows(IllegalArgumentException.class, () -> new Task(null, "Test Task", "This is a test task."));
		assertThrows(IllegalArgumentException.class, () -> new Task("12345678901", "Test Task", "This is a test task."));
	}
	
	@Test
	public void testTaskCreationInvalidName() {
		assertThrows(IllegalArgumentException.class, () -> new Task("1", null, "This is a test task."));
		assertThrows(IllegalArgumentException.class, () -> new Task("1", "This name is way to long to be valid", "This is a test task."));
	}
	
	@Test
	public void testTaskCreationInvalidDescription() {
		assertThrows(IllegalArgumentException.class, () -> new Task("1","Test Task", null));
		assertThrows(IllegalArgumentException.class, () -> new Task ("1","Test Task", "This description is way too long to be valid. It exceeds the maximum allowed length of fifty characters"));
	}
	
	@Test 
	public void testSetNameValid() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		task.setName("Updated Name");
		assertEquals("Updated Name", task.getName());
	}
	
	@Test
	public void testSetNameInvalid() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		assertThrows(IllegalArgumentException.class, () -> task.setName(null));
		assertThrows(IllegalArgumentException.class, () -> task.setName("This name is way to long to be valid"));
	}
	
	@Test
	public void testSetDescriptionValid() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		task.setDescription("Updated Description");
		assertEquals("Updated Description", task.getDescription());
	}
	
	@Test
	public void testSetDescriptionInvalid() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		assertThrows(IllegalArgumentException.class, () -> task.setDescription(null));
		assertThrows(IllegalArgumentException.class, () -> task.setDescription("This description is way to long to be valid. It exceeds the maximum allowed length of fifty characters."));
	}
	
	
	
}
