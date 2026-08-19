#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ===============================
// LCD CONFIGURATION
// ===============================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===============================
// OPTIONAL SERVO
// ===============================
#define USE_SERVO 1

#if USE_SERVO
Servo gateServo;
const int SERVO_PIN = 11;
#endif

// ===============================
// SENSOR PINS
// ===============================

const byte NUM_SLOTS = 4;

const byte trigPins[NUM_SLOTS] = {
  2, 4, 6, 8
};

const byte echoPins[NUM_SLOTS] = {
  3, 5, 7, 9
};

// ===============================
// OUTPUT PINS
// ===============================

const byte BUZZER_PIN = 10;
const byte GREEN_LED = 12;
const byte RED_LED = 13;

// ===============================
// PARKING CONFIGURATION
// ===============================

// Distance below this value means
// vehicle detected.

const float OCCUPIED_THRESHOLD = 20.0;

// Maximum valid sensor distance
const float MAX_DISTANCE = 400.0;

// ===============================
// SLOT STATE
// ===============================

bool occupied[NUM_SLOTS];

float distances[NUM_SLOTS];

int availableSlots = 0;

// ===============================
// SETUP
// ===============================

void setup() {

  Serial.begin(9600);

  // Configure ultrasonic pins
  for (byte i = 0; i < NUM_SLOTS; i++) {

    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);

    digitalWrite(trigPins[i], LOW);
  }

  // Configure outputs
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

#if USE_SERVO
  gateServo.attach(SERVO_PIN);
  gateServo.write(0);   // Gate initially closed
#endif

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(1500);

  Serial.println("==============================");
  Serial.println(" SMART PARKING SYSTEM");
  Serial.println("==============================");
}

// ===============================
// ULTRASONIC DISTANCE FUNCTION
// ===============================

float measureDistance(byte trigPin, byte echoPin) {

  // Make sure trigger starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 microsecond trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse
  unsigned long duration = pulseIn(
    echoPin,
    HIGH,
    30000
  );

  // Timeout / invalid reading
  if (duration == 0) {
    return -1;
  }

  // Distance in cm
  float distance = duration / 58.0;

  // Validate range
  if (distance <= 0 || distance > MAX_DISTANCE) {
    return -1;
  }

  return distance;
}

// ===============================
// READ ALL SENSORS
// ===============================

void readAllSensors() {

  for (byte i = 0; i < NUM_SLOTS; i++) {

    distances[i] = measureDistance(
      trigPins[i],
      echoPins[i]
    );

    // Small delay reduces cross-talk
    // between ultrasonic sensors.
    delay(50);
  }
}

// ===============================
// DETERMINE SLOT STATUS
// ===============================

void updateSlotStates() {

  availableSlots = 0;

  for (byte i = 0; i < NUM_SLOTS; i++) {

    // Invalid reading:
    // treat as FREE for this beginner implementation,
    // but report it through Serial Monitor.
    if (distances[i] < 0) {

      occupied[i] = false;

      Serial.print("Slot ");
      Serial.print(i + 1);
      Serial.println(": INVALID READING");

      continue;
    }

    if (distances[i] < OCCUPIED_THRESHOLD) {

      occupied[i] = true;

    } else {

      occupied[i] = false;
      availableSlots++;
    }
  }
}

// ===============================
// UPDATE LED STATUS
// ===============================

void updateLEDs() {

  if (availableSlots > 0) {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

  } else {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
}

// ===============================
// BUZZER CONTROL
// ===============================

void updateBuzzer() {

  if (availableSlots == 0) {

    tone(BUZZER_PIN, 1000);

  } else {

    noTone(BUZZER_PIN);
  }
}

// ===============================
// SERVO GATE CONTROL
// ===============================

void updateGate() {

#if USE_SERVO

  if (availableSlots > 0) {

    // Open gate
    gateServo.write(90);

  } else {

    // Close gate
    gateServo.write(0);
  }

#endif
}

// ===============================
// LCD DISPLAY
// ===============================

void updateLCD() {

  // Page 1
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(occupied[0] ? "OCC " : "FREE");

  lcd.setCursor(9, 0);
  lcd.print("S2:");
  lcd.print(occupied[1] ? "OCC" : "FREE");

  lcd.setCursor(0, 1);
  lcd.print("S3:");
  lcd.print(occupied[2] ? "OCC " : "FREE");

  lcd.setCursor(9, 1);
  lcd.print("S4:");
  lcd.print(occupied[3] ? "OCC" : "FREE");

  delay(1500);

  // Page 2
  lcd.clear();

  if (availableSlots == 0) {

    lcd.setCursor(0, 0);
    lcd.print("PARKING FULL");

    lcd.setCursor(0, 1);
    lcd.print("No Space!");

  } else {

    lcd.setCursor(0, 0);
    lcd.print("Available:");

    lcd.print(availableSlots);

    lcd.setCursor(0, 1);
    lcd.print("Slots Free");
  }

  delay(1500);
}

// ===============================
// SERIAL MONITOR
// ===============================

void printSerialData() {

  Serial.println();
  Serial.println("------------------------------");

  for (byte i = 0; i < NUM_SLOTS; i++) {

    Serial.print("Slot ");
    Serial.print(i + 1);
    Serial.print(" | ");

    if (distances[i] < 0) {

      Serial.println("Invalid reading");

    } else {

      Serial.print("Distance = ");
      Serial.print(distances[i]);
      Serial.print(" cm | ");

      if (occupied[i]) {

        Serial.println("OCCUPIED");

      } else {

        Serial.println("FREE");
      }
    }
  }

  Serial.print("Available Slots = ");
  Serial.println(availableSlots);

  if (availableSlots == 0) {

    Serial.println("STATUS: PARKING FULL");

  } else {

    Serial.println("STATUS: SPACE AVAILABLE");
  }

  Serial.println("------------------------------");
}

// ===============================
// MAIN LOOP
// ===============================

void loop() {

  // 1. Read ultrasonic sensors
  readAllSensors();

  // 2. Determine slot states
  updateSlotStates();

  // 3. Count and display information
  updateLEDs();

  // 4. Parking-full alert
  updateBuzzer();

  // 5. Optional barrier gate
  updateGate();

  // 6. LCD
  updateLCD();

  // 7. Serial debugging
  printSerialData();

  delay(500);
}