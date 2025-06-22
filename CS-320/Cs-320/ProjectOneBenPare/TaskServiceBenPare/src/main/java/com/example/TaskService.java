package com.example;

import java.util.HashMap;
import java.util.Map;

public class TaskService {
	private Map<String, Task> tasks;
	
	//constructor
	public TaskService() {
		tasks = new HashMap<>();
	}
	
	public void addTask(Task task) {
		if(tasks.containsKey(task.getTaskId())) {
			throw new IllegalArgumentException("Task ID must be unique.");
		}
		tasks.put(task.getTaskId(),task);	
	}
	
	public void deleteTask(String taskId) {
		if(!tasks.containsKey(taskId)) {
			throw new IllegalArgumentException("Task ID not found.");
		}
		tasks.remove(taskId);
	}
	
	public void updateTaskName(String taskId, String name) {
		Task task = tasks.get(taskId);
		if(task == null) {
			throw new IllegalArgumentException("Task ID not found.");
		}
		task.setName(name);
	}
	
	public void updateTaskDescription(String taskId, String description) {
		Task task = tasks.get(taskId);
		if(task == null) {
			throw new IllegalArgumentException("Task ID not found");
		}
		task.setDescription(description);
	}
	public Task getTask(String taskId) {
		return tasks.get(taskId);
	}	
}
