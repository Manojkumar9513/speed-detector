#include <LiquidCrystal.h>

// LCD connections (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// IR sensor pins
const int sensor1 = 8;
const int sensor2 = 9;

// Distance between sensors (in meters)
const float DISTANCE_METERS = 0.30; // 30 cm

unsigned long tStart = 0;
bool started = false;

void setup() {
 lcd.begin(16, 2);        // initialize the display
 lcd.print("Speed Tracker");
 delay(2000);
 lcd.clear();

 pinMode(sensor1, INPUT);
 pinMode(sensor2, INPUT);
}

void loop() {
 // Wait for sensor1 trigger
 if (!started && digitalRead(sensor1) == LOW) {
   tStart = micros();  // record time
   started = true;
   lcd.clear();
   lcd.print("Timing...");
 }

 // Wait for sensor2 if started
 if (started && digitalRead(sensor2) == LOW) {
   unsigned long tEnd = micros(); // record stop time
   started = false;

   // Time difference in seconds
   float timeSec = (tEnd - tStart) / 1000000.0;

   // Calculate speed (m/s → km/h)
   float speedMps = DISTANCE_METERS / timeSec;
   float speedKmh = speedMps * 3.6;

   // Display on LCD
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Speed:");

   lcd.setCursor(0, 1);
   lcd.print(speedKmh);
   lcd.print(" km/h");

   delay(3000);  // wait before next measurement
 }
}