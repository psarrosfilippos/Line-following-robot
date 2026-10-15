# Autonomous 5-Channel Line-Tracking Mobile Robot

Firmware, circuit architecture, and mechanical simulation for an autonomous differential-drive robot designed for closed-loop line following and trajectory recovery.

## Overview

The vehicle utilizes a 5-channel infrared (IR) reflection array positioned at the chassis underside to track a high-contrast path. An onboard ATmega328P microcontroller evaluates tracking errors across 9 discrete sensory states and actuates dual geared DC motors through an L293D H-Bridge driver with independent PWM speed modulation.

## System Architecture

### Hardware Components
* **Microcontroller:** Arduino Uno R3 (ATmega328P @ 16 MHz)
* **Motor Driver:** L293D Dual H-Bridge IC
* **Actuators:** 2x DC Geared Motors (Differential Drive)
* **Sensors:** 5-Channel Infrared Reflective Array (L1, L2, M, R2, R1)
* **Power Regulation:** L7805CV linear regulator isolating logic and sensor rails from inductive motor noise
* **Power Source:** 9V DC supply

### Pin Mapping

| Peripheral | Signal / Function | Arduino Pin | Mode |
| :--- | :--- | :--- | :--- |
| **Motor A (Left)** | Direction Forward (+) | Pin 13 | OUTPUT |
| | Direction Reverse (-) | Pin 12 | OUTPUT |
| | Speed Control (PWM) | Pin 11 | OUTPUT |
| **Motor B (Right)** | Speed Control (PWM) | Pin 10 | OUTPUT |
| | Direction Reverse (-) | Pin 9 | OUTPUT |
| | Direction Forward (+) | Pin 8 | OUTPUT |
| **IR Array** | Far-Left Sensor (L1) | Pin 6 | INPUT |
| | Inner-Left Sensor (L2) | Pin 5 | INPUT |
| | Center Sensor (M) | Pin 4 | INPUT |
| | Inner-Right Sensor (R2) | Pin 3 | INPUT |
| | Far-Right Sensor (R1) | Pin 2 | INPUT |

## Decision Logic & Steering Matrix

The firmware operates on active-low sensor detection (`0` = Line Detected / Black, `1` = Surface / White):

| L1 | L2 | M | R2 | R1 | Motion State | Function | PWM (L : R) | Steering Action |
| :---: | :---: | :---: | :---: | :---: | :--- | :--- | :---: | :--- |
| 1 | 1 | 0 | 1 | 1 | Centered | `forward()` | 80 : 80 | Balanced straight drive |
| 1 | 0 | 0 | 1 | 1 | Slight Right Drift | `leftS()` | 70 : 60 | Gentle differential left correction |
| 1 | 0 | 1 | 1 | 1 | Moderate Drift | `left()` | 70 : 50 | Standard left turn |
| 0 | 0 | 0 | 1 | 1 | Sharp Right Drift | `leftF()` | 60 : 60 | Pivot left turn (motors in counter-rotation) |
| 1 | 1 | 0 | 0 | 1 | Slight Left Drift | `rightS()` | 60 : 70 | Gentle differential right correction |
| 1 | 1 | 1 | 0 | 1 | Moderate Drift | `right()` | 50 : 70 | Standard right turn |
| 1 | 1 | 0 | 0 | 0 | Sharp Left Drift | `rightF()` | 60 : 60 | Pivot right turn (motors in counter-rotation) |
| 1 | 1 | 1 | 1 | 1 | Track Loss | `backward()` | 60 : 60 | Reverse backtrack until line re-acquisition |
| 0 | 0 | 0 | 0 | 0 | Goal / Stop Marker | `stopRobot()` | 0 : 0 | Full motor cut-off |

## Design & Prototyping Workflow

* **Circuit Schematic:** Designed using EasyEDA with common ground planes and inductive filtering.
* **Firmware Validation:** Simulated in Autodesk Tinkercad Circuits to verify timing, PWM modulation, and logic states.

## Installation & Flashing

1. Open `line_follower.ino` inside the **Arduino IDE**.
2. Select target board: **Tools > Board > Arduino Uno**.
3. Select the active COM port: **Tools > Port**.
4. Verify and upload the sketch to the microcontroller.

## Future Improvements

* [ ] Transition from discrete state thresholds to a continuous Proportional-Integral-Derivative (PID) controller.
* [ ] Integrate an ultrasonic sensor (HC-SR04) for dynamic obstacle detection and avoidance.
* [ ] Migrate power subsystem to 2S/3S Li-Ion cells with dedicated BMS circuitry.

## Author

**Filippos Psarros**
* MSc Candidate in Unmanned Autonomous and Remote-Controlled Systems (University of West Attica)
* BSc in Informatics and Telecommunications (Computational Systems)
