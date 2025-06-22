package com.example;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class TaskServiceTest {
	
	private TaskService taskService;
	
	@BeforeEach
	public void setUp() {
		taskService = new TaskService();
	}
	
	@Test
	public void testAddTask() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		taskService.addTask(task);
		assertEquals(task, taskService.getTask("1"));
	}
	
	@Test
	public void testAddTaskWithDuplicateId() {
		Task task1 = new Task("1", "Test Task 1", "This is a test task 1.");
		Task task2 = new Task("1", "Test Task2", "This is a test task 2.");
		taskService.addTask(task1);
		assertThrows(IllegalArgumentException.class, () -> taskService.addTask(task2));
	}
	
	@Test
	public void testDeleteTask() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		taskService.addTask(task);
		taskService.deleteTask("1");
		assertNull(taskService.getTask("1"));
	}
	
	@Test
	public void testDeleteTaskWithNonExistentId() {
		assertThrows(IllegalArgumentException.class, () -> taskService.deleteTask("nonexistent"));
	}
	@Test
	public void testUpdateTaskName() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		taskService.addTask(task);
		taskService.updateTaskName("1", "Updated Task Name");
		assertEquals("Updated Task Name", taskService.getTask("1").getName());
	}
	@Test
	public void testUpdateTaskDescription() {
		Task task = new Task("1", "Test Task", "This is a test task.");
		taskService.addTask(task);
		taskService.updateTaskDescription("1", "Updated Task Description");
		assertEquals("Updated Task Description", taskService.getTask("1").getDescription());
	}
	@Test 
	public void testUpdateTaskWithNonExistentId() {
		assertThrows(IllegalArgumentException.class, () -> taskService.updateTaskName("nonexistent","New Name"));
		assertThrows(IllegalArgumentException.class, () -> taskService.updateTaskDescription("nonexistent", "New Description"));
	}

}
