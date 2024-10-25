// Define pins for motors and sensor
const int trigPin = 8;     // Trig pin for the ultrasonic sensor
const int echoPin = 9;     // Echo pin for the ultrasonic sensor
const int motor1Pin1 = 2;  // Motor 1 pin
const int motor1Pin2 = 3;  // Motor 1 pin
const int motor2Pin1 = 4;  // Motor 2 pin
const int motor2Pin2 = 5;  // Motor 2 pin

// Distance threshold in centimeters
const int distanceThreshold = 20;

void setup() {
  // Set motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Set sensor pins as output and input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

// Function to measure distance
long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Convert to centimeters
  return distance;
}

// Function to make the car move forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to rotate left (90 degrees)
void rotateLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void loop() {
  // Read the distance from the sensor
  long distance = readDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > distanceThreshold) {
    // If there is no obstacle, move forward
    moveForward();
  } else {
    // If there is an obstacle, stop
    stopMotors();
    delay(500);

    // Move backward for 0.5 seconds
    moveBackward();
    delay(500);

    // Stop and rotate left by 90 degrees
    stopMotors();
    rotateLeft();
    delay(500); // Adjust duration based on motor speed to achieve exact 90 degrees
    stopMotors();
    delay(500);

    // Check again if there is an obstacle ahead
    distance = readDistance();
    if (distance > distanceThreshold) {
      // If there is no longer an obstacle, resume moving forward
      moveForward();
    }
    // If there is still an obstacle, the loop will repeat the process
  }
}
