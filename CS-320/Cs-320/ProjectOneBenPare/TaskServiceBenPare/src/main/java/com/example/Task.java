package com.example;



public class Task {
	private final String taskId;
	private String name;
	private String description;
	
	//Task object cannot be created with invalid data
	//Constructor
	public Task(String taskId, String name, String description) {
		if(taskId == null || taskId.length() > 10) {
			throw new IllegalArgumentException("Task ID must not be null and must be at most 10 charecters long.");
		}
		if(name == null || name.length() > 20) {
			throw new IllegalArgumentException("Name must not be null and must be at most 20 charecters long.");
		}
		if(description == null || description.length()>50) {
			throw new IllegalArgumentException("Description must not be null and must be at most 50 charecters long.");
		}
		this.taskId = taskId;
		this.name = name;
		this.description = description;
	}	
	
	//getter for taskId
	public String getTaskId() {
		return taskId;
	}
	public String getName() {
		return name;
	}
	//setter for name
	//task object cannot be modified with invalid data
	public void setName(String name) {
		if(name == null || name.length()>20) {
			throw new IllegalArgumentException("Name must not be null and be at most 20 charecters long");
	}	
		this.name = name;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		if(description == null || description.length() > 50) {
			throw new IllegalArgumentException("Description must not be null and must be at most 50 charecters");
		}
		this.description = description;
	}
	
}
