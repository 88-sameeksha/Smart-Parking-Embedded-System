Test 1 — Empty parking
set-
S1 = 30 cm
S2 = 30 cm
S3 = 30 cm
S4 = 30 cm

Expected-
S1 FREE
S2 FREE
S3 FREE
S4 FREE

Available = 4
Green LED:

ON

Red LED:

OFF

Buzzer:

OFF


Test 2 — One vehicle

Change Sensor 1:

S1 = 10 cm

Expected:

S1 OCCUPIED
S2 FREE
S3 FREE
S4 FREE

Available = 3



Test 3 — Three occupied
S1 = 10 cm
S2 = 12 cm
S3 = 8 cm
S4 = 30 cm

Expected:

S1 OCC
S2 OCC
S3 OCC
S4 FREE

Available = 1




Test 4 — Full parking
S1 = 10 cm
S2 = 12 cm
S3 = 8 cm
S4 = 15 cm

Expected:

Available = 0

LCD:

PARKING FULL
No Space!

Red LED:

ON

Buzzer:

ON

Servo:

CLOSED


Test 5 — Vehicle leaves

Change:

S3 = 30 cm

Expected:

Available = 1

Buzzer:

OFF

Green LED:

ON