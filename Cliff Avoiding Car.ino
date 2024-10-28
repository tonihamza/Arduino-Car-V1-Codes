// Define motor pins
const int motor1Pin1 = 2;  // Motor 1
const int motor1Pin2 = 3;  // Motor 1
const int motor2Pin1 = 4;  // Motor 2
const int motor2Pin2 = 5;  // Motor 2

// Define IR sensor pins
const int irSensorLeft = 6;  // Left IR sensor (downward facing)
const int irSensorRight = 7; // Right IR sensor (downward facing)

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

// Function to rotate in place 90 degrees to the right
void rotateRight() {
  digitalWrite(motor1Pin1, HIGH);  // Left motor forward
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);   // Right motor backward
  digitalWrite(motor2Pin2, HIGH);
  delay(400); // Adjust this delay to achieve a 90-degree rotation
  stopMotors();
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
  int leftEdge = digitalRead(irSensorLeft);
  int rightEdge = digitalRead(irSensorRight);

  Serial.print("Left Sensor: ");
  Serial.print(leftEdge);
  Serial.print(" Right Sensor: ");
  Serial.println(rightEdge);

  // Determine action based on sensor readings
  if (leftEdge == HIGH && rightEdge == HIGH) {
    // Both sensors detect surface - move forward
    moveForward();
  } else if (leftEdge == LOW && rightEdge == HIGH) {
    // Left sensor detects edge, right sensor on surface - turn right
    turnRight();
    delay(300);  // Short delay to allow rotation
  } else if (rightEdge == LOW && leftEdge == HIGH) {
    // Right sensor detects edge, left sensor on surface - turn left
    turnLeft();
    delay(300);  // Short delay to allow rotation
  } else {
    // Both sensors detect edge - stop, move back, rotate
    stopMotors();
    delay(500);  // Wait 0.5 seconds

    moveBackward();  // Move backward briefly
    delay(500);      // Move backward for 0.5 seconds

    rotateRight();   // Rotate 90 degrees to the right
  }

  // Optional small delay for stability
  delay(100);
}
