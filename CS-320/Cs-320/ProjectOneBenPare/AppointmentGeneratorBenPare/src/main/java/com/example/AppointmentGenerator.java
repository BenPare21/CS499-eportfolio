package com.example.appointment;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class AppointmentGenerator {
    private static final String[] DESCRIPTIONS = {
        "Doctor Visit", "Team Meeting", "Coffee with Client", "Code Review", "Lunch Break"
    };

    public static void main(String[] args) {
        List<Appointment> appointments = generateAppointments(5);
        for (Appointment appt : appointments) {
            System.out.println(appt);
        }
    }

    public static List<Appointment> generateAppointments(int count) {
        List<Appointment> list = new ArrayList<>();
        Random rand = new Random();
        for (int i = 0; i < count; i++) {
            String id = "APT-" + (1000 + rand.nextInt(9000));
            String description = DESCRIPTIONS[rand.nextInt(DESCRIPTIONS.length)];
            LocalDateTime date = LocalDateTime.now().plusDays(rand.nextInt(30)).withHour(9 + rand.nextInt(8)).withMinute(0);

            list.add(new Appointment(id, description, date));
        }
        return list;
    }

    static class Appointment {
        String id;
        String description;
        LocalDateTime time;

        public Appointment(String id, String description, LocalDateTime time) {
            this.id = id;
            this.description = description;
            this.time = time;
        }

        @Override
        public String toString() {
            return "Appointment{" +
                    "id='" + id + '\'' +
                    ", description='" + description + '\'' +
                    ", time=" + time +
                    '}';
        }
    }
}
