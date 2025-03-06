#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// OLED Display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin (or -1 if not used)
#define OLED_I2C_ADDRESS 0x3D // Replace with your OLED display's I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// GPS settings
SoftwareSerial gpsSerial(4, 15); // RX, TX for GPS module
TinyGPSPlus gps;

// Alcohol sensor pin
const int alcoholPin = A5;

// Define your alcohol threshold
const int THRESHOLD = 100; // Change this value based on your requirements

void setup() {
  // Initialize the OLED display
  display.begin(OLED_I2C_ADDRESS, 21, 22); // I2C address and SDA, SCL pins
  display.display();
  
  // Initialize GPS module
  gpsSerial.begin(9600);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read alcohol sensor value
  int alcoholValue = analogRead(alcoholPin);
  
  // Clear the OLED display
  display.clearDisplay();
  
  if (alcoholValue > THRESHOLD) {
    // Display "Alcohol Alert" on OLED
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE); // Corrected here
    display.setCursor(0, 0);
    display.println("Alcohol Alert");
    display.display();
    
    // Lock the engine or trigger an alarm here
    // Implement your engine locking or alarm logic
    
    // Example: Lock the engine (replace with your logic)
    // digitalWrite(engineLockPin, HIGH);
  }
  
  // Read GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Retrieve GPS data and use it as needed
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);
    }
  }
  
  delay(1000); // Delay for a second (adjust as needed)
}