Trigger
 ↓
Echo
 ↓
Time
 ↓
Distance
 ↓
Threshold
 ↓
Slot State
 ↓
Available Count


ALGORITHM--------------------

START
 ↓
Initialize sensors
 ↓
Initialize LCD/output devices
 ↓
Read sensor
 ↓
Calculate distance
 ↓
Distance < threshold?
 ├── YES → OCCUPIED
 └── NO  → FREE
 ↓
Count free slots
 ↓
Update LCD
 ↓
Update LEDs
 ↓
Parking full?
 ├── YES → Buzzer + gate closed
 └── NO  → Normal operation
 ↓
Repeat