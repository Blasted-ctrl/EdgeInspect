# What are you actually building?

A mini industrial inspection machine.
An object is placed on/in front of the machine.
The camera looks at it.
ML decides what the object is / whether it is defective.
Other sensors check the physical situation.
The ESP32 makes the final decision.
A servo/motor physically accepts or rejects the object.
If something goes wrong, the system detects the problem and attempts to recover.

# Final flow

Object
  ↓
Camera
  ↓
Computer Vision
  ↓
ML Prediction
  ↓
Sensor Fusion
  ↓
C++ State Machine
  ↓
Decision
  ↓
Servo/Motor
  ↓
PASS / REJECT