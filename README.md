# Arduino Smart Car

The **Arduino Smart Car** is a versatile 3D-printed vehicle platform designed for a wide range of Arduino-based robotics projects. This car comes with all the components necessary to build and program a fully functional smart car, making it perfect for obstacle avoidance, line-following, or even internet-controlled robotics experiments. With easy assembly and a modular design, it is ideal for both beginners and experienced hobbyists.

## Components

The Arduino Smart Car consists of several key components:

- **Car Base**: The foundation of the car, providing space to mount all the necessary components. It includes dedicated slots for three 9V batteries at the rear to power the vehicle.
  
- **Ultrasonic Sensor Mount**: A two-part support structure at the front holds an ultrasonic distance sensor in place, allowing the car to detect obstacles and make intelligent navigation decisions.
  
- **Line Detection Sensors**: Two line-detection sensors mounted at the front of the car enable it to follow lines on the ground—ideal for line-following projects.
  
- **Arduino Uno and H-Bridge Motor Controller**: The car is controlled by an Arduino Uno mounted in the center of the base, which acts as the brain of the car. An H-Bridge motor controller is also installed to manage the two 5V DC motors that drive the wheels. Each motor controls one wheel, allowing for differential steering.
  
- **Metal Ball Caster Wheel**: At the front of the car, a metal ball caster wheel provides smooth motion and stability while moving.
  
- **Modular Design for NodeMCU**: For more advanced projects, the car comes with a special mount that allows you to swap out the Arduino Uno for a NodeMCU, enabling internet connectivity for remote control or IoT applications.

## Assembly Instructions

1. **Gather Components**: Ensure you have all the necessary components as listed above.
2. **Attach Motors**: Secure the two 5V DC motors to the designated slots on the car base.
3. **Mount the Wheels**: Attach the wheels to the motors and install the metal ball caster wheel at the front for stability.
4. **Install Sensors**: Fix the ultrasonic sensor and line detection sensors in their respective mounts.
5. **Connect Wiring**: Use the wiring provided in the electrical diagram section below to connect the motors and sensors to the Arduino Uno or NodeMCU.
6. **Power Setup**: Place the 9V batteries in the designated slots at the rear of the car.
7. **Final Checks**: Ensure all components are securely mounted and connections are properly made before powering on the car.

### Electrical Diagram

!(insert_link_to_electrical_diagram_here)

*This diagram illustrates the wiring configuration for the Arduino Smart Car. Make sure to follow the connections as shown for proper functionality.*

## Project Codes

Here are the different codes available for the Arduino Smart Car, along with their purposes:

### 1. **BlynkSmartCar.ino**
This code enables remote control of the smart car via the Blynk app. It utilizes a joystick for directional movement and displays sensor statuses through virtual LEDs. It also measures distance using an ultrasonic sensor.

### 2. **Cliff Avoiding Car.ino**
This code allows the car to detect edges or cliffs using an ultrasonic sensor. When the sensor detects a drop, the car stops, reverses briefly, and makes a 90-degree turn to avoid falling off the edge.

### 3. **Line Follower Car.ino**
The line follower code enables the car to detect and follow a line on the ground using infrared sensors. It adjusts its movements based on the sensor readings to stay on the track.

### 4. **Obstacle-Avoiding Car.ino**
This code allows the car to navigate around obstacles using the ultrasonic sensor. If an obstacle is detected within a certain range, the car will stop, back up, and then make a turn to avoid the obstacle.

## Conclusion

The Arduino Smart Car is a highly customizable, modular platform that provides endless opportunities for creative robotics projects. Its easy-to-assemble design and flexibility make it a great choice for anyone looking to explore the world of Arduino and NodeMCU-controlled robotics. Whether you’re building a line-following car, a self-driving vehicle, or a Wi-Fi-enabled smart car, this kit has everything you need to bring your ideas to life.

**Check the GitHub repository for the code.
