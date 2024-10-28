// Define motor pins
const int motor1Pin1 = 2;  // Motor 1
const int motor1Pin2 = 3;  // Motor 1
const int motor2Pin1 = 4;  // Motor 2
const int motor2Pin2 = 5;  // Motor 2

// Define IR sensor pins
const int irSensorLeft = 6;  // Left IR sensor (digital)
const int irSensorRight = 7; // Right IR sensor (digital)

void setup() {
  // Set motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Set IR sensor pins as input
  pinMode(irSensorLeft, INPUT);
  pinMode(irSensorRight, INPUT);

  // Initialize serial for debugging
  Serial.begin(9600);
}

// Function to move forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
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

void loop() {
  // Read values from IR sensors
  int leftState = digitalRead(irSensorLeft);
  int rightState = digitalRead(irSensorRight);
  
  Serial.print("Left Sensor: ");
  Serial.print(leftState);
  Serial.print(" Right Sensor: ");
  Serial.println(rightState);

  // Determine action based on sensor readings
  if (leftState == HIGH && rightState == HIGH) {
    // Both sensors see white - move forward
    moveForward();
  } else if (leftState == LOW && rightState == HIGH) {
    // Left sensor sees black (line), right sees white - turn right
    turnRight();
  } else if (rightState == LOW && leftState == HIGH) {
    // Right sensor sees black (line), left sees white - turn left
    turnLeft();
  } else {
    // Both sensors on line (unexpected case) - stop
    stopMotors();
  }
}
