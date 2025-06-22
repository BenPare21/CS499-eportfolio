package com.example.appointment;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class AppointmentGeneratorTest {

    @Test
    public void testGenerateAppointmentsCount() {
        List<AppointmentGenerator.Appointment> appointments = AppointmentGenerator.generateAppointments(5);
        assertEquals(5, appointments.size(), "Should generate 5 appointments");
    }

    @Test
    public void testAppointmentsNotNull() {
        List<AppointmentGenerator.Appointment> appointments = AppointmentGenerator.generateAppointments(3);
        for (AppointmentGenerator.Appointment appt : appointments) {
            assertNotNull(appt.id);
            assertNotNull(appt.description);
            assertNotNull(appt.time);
        }
    }

    @Test
    public void testAppointmentIdFormat() {
        List<AppointmentGenerator.Appointment> appointments = AppointmentGenerator.generateAppointments(1);
        String id = appointments.get(0).id;
        assertTrue(id.startsWith("APT-"), "ID should start with 'APT-'");
    }
}
