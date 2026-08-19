 
 ARCHITECTURE-----------------------
 
                 ┌─────────────────┐
                 │ Parking Slot 1  │
                 │   HC-SR04       │
                 └────────┬────────┘
                          │
                 ┌────────▼────────┐
                 │ Parking Slot 2  │
                 │   HC-SR04       │
                 └────────┬────────┘
                          │
                 ┌────────▼────────┐
                 │ Parking Slot 3  │
                 │   HC-SR04       │
                 └────────┬────────┘
                          │
                 ┌────────▼────────┐
                 │ Parking Slot 4  │
                 │   HC-SR04       │
                 └────────┬────────┘
                          │
                          ▼
                ┌───────────────────┐
                │    Arduino UNO     │
                │                   │
                │ Distance Reading  │
                │       ↓           │
                │ Threshold Logic   │
                │       ↓           │
                │ Slot State        │
                │       ↓           │
                │ Available Count   │
                └───────┬───────────┘
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
      ┌───────┐     ┌───────┐    ┌────────┐
      │ LCD   │     │ LEDs  │    │ Buzzer │
      └───────┘     └───────┘    └────────┘
                                      │
                                      ▼
                                Optional Servo