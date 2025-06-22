package com.example;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class AppointmentService {
    private Map<String, Appointment> appointments;

    // Constructor
    public AppointmentService() {
        appointments = new HashMap<>();
    }
    
    public boolean addAppointment(Appointment appointment) {
        if (appointment == null || appointments.containsKey(appointment.getAppointmentID())) {
            return false;
        }
        appointments.put(appointment.getAppointmentID(), appointment);
        return true;
    }

    public boolean deleteAppointment(String appointmentID) {
        if (appointmentID == null || !appointments.containsKey(appointmentID)) {
            return false;
        }
        appointments.remove(appointmentID);
        return true;
    }

    public Appointment getAppointment(String appointmentID) {
        return appointments.get(appointmentID);
    }
    
    //New method to update appointment date, added in response to feedback
    public boolean updateAppointmentDate(String appointmentID, Date newDate) {
    	Appointment appointment = getAppointment(appointmentID);
    	if(appointment != null) {
    		appointment.setAppointmentDate(newDate);
    		return true;
    	}
    	return false;
    }
    
    //New method to update appointment description, added in response to feedback
    public boolean updateAppointmentDescription(String appointmentID, String newDescription) {
    	Appointment appointment = getAppointment(appointmentID);
    	if(appointment != null) {
    		appointment.setDescription(newDescription);
    		return true;
    	}
    	return false;
    }
    
    
    
    
}
