#define BLYNK_TEMPLATE_ID "YourTemplateID" // Update with your template ID
#define BLYNK_DEVICE_NAME "YourDeviceName"  // Update with your device name
#define BLYNK_AUTH_TOKEN "YourAuthToken"    // Update with your Blynk auth token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h> // Include for ESP32 (NodeMCU is ESP8266)
#include <BlynkWidgets.h> // Include Blynk Widgets

// WiFi credentials
char ssid[] = "YourSSID"; // Your WiFi SSID
char pass[] = "YourPassword"; // Your WiFi Password

// Motor pins
const int motor1Pin1 = D1;  // Motor 1
const int motor1Pin2 = D2;  // Motor 1
const int motor2Pin1 = D3;  // Motor 2
const int motor2Pin2 = D4;  // Motor 2

// IR sensors
const int irSensorLeft = D5;
const int irSensorRight = D6;

// Ultrasonic sensor
const int trigPin = D7;
const int echoPin = D8;

// Blynk virtual pins
#define JOYSTICK_VPIN V1      // Virtual pin for joystick
#define LEFT_LED_VPIN V2      // Virtual pin for left IR sensor LED
#define RIGHT_LED_VPIN V3     // Virtual pin for right IR sensor LED
#define DISTANCE_VPIN V4      // Virtual pin for distance display

BlynkTimer timer;

// Function to measure distance
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Calculate distance in cm
  
  return distance;
}

// Function to move forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to turn left
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn right
void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to stop motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Joystick control
BLYNK_WRITE(JOYSTICK_VPIN) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  
  if (y > 200) {
    moveForward();
  } else if (y < 100) {
    moveBackward();
  } else if (x < 100) {
    turnLeft();
  } else if (x > 200) {
    turnRight();
  } else {
    stopMotors();
  }
}

// Function to update sensor status on Blynk
void updateSensors() {
  int leftEdge = digitalRead(irSensorLeft);
  int rightEdge = digitalRead(irSensorRight);

  // Write to virtual LEDs based on IR sensor readings
  if (leftEdge) {
    Blynk.virtualWrite(LEFT_LED_VPIN, 255); // Turn on LED if left IR sensor detects ground
  } else {
    Blynk.virtualWrite(LEFT_LED_VPIN, 0);   // Turn off LED if left IR sensor does not detect ground
  }

  if (rightEdge) {
    Blynk.virtualWrite(RIGHT_LED_VPIN, 255); // Turn on LED if right IR sensor detects ground
  } else {
    Blynk.virtualWrite(RIGHT_LED_VPIN, 0);   // Turn off LED if right IR sensor does not detect ground
  }

  // Measure and display distance on Blynk
  long distance = measureDistance();
  Blynk.virtualWrite(DISTANCE_VPIN, String(distance) + " cm");
}

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Initialize sensor pins
  pinMode(irSensorLeft, INPUT);
  pinMode(irSensorRight, INPUT);
  
  // Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set timer to update sensors every 500 ms
  timer.setInterval(500L, updateSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}
