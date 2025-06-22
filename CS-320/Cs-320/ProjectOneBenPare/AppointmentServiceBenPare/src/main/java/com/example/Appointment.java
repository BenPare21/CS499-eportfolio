package com.example;

import java.util.Date;

public class Appointment {
	private final String appointmentID;
	private Date appointmentDate; //Removed final to allow changes
	private String description; // Removed final to allow changes
	
	public Appointment(String appointmentID, Date appointmentDate, String description) {
		if (appointmentID == null || appointmentID.length() > 10) {
			throw new IllegalArgumentException("Invalid appointment ID");
		}
		if(appointmentDate == null || appointmentDate.before(new Date())) {
			throw new IllegalArgumentException("Invalid appointment date");
		}
		if(description == null || description.length()>50) {
			throw new IllegalArgumentException("Invalid description");
		}
		this.appointmentID = appointmentID;
		this.appointmentDate = appointmentDate;
		this.description = description;
	}
	public String getAppointmentID() {
		return appointmentID;
	}
	public Date getAppointmentDate() {
		return appointmentDate;
	}
	//Setter method for appointmentDate added based on feedback to make this field mutable
	public void setAppointmentDate(Date appointmentDate) {
		if(appointmentDate == null || appointmentDate.before(new Date())) {
			throw new IllegalArgumentException("Invalid appointment date");
		}
		this.appointmentDate = appointmentDate;
	}
	
	public String getDescription() {
		return description;
	}
	
	//Setter method for description added based on feedback to make this field mutable
	public void setDescription(String description) {
		if(description == null || description.length() > 50) {
			throw new IllegalArgumentException("Invalid description");
		}
		this.description = description;
	}

}
