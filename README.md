# EdgeInspect

Handwritten code project I built to learn ESP32. Use it if you'd like :)

## What it is

A mini industrial inspection machine. You put an object in front of it, a camera looks at it, a small ML model decides whether it is normal or defective, a few sensors check the physical situation, and the ESP32 makes the final call. A servo then physically accepts or rejects the object.

```
Object -> Camera -> Computer Vision -> ML Prediction -> Sensor Fusion
       -> State Machine -> Decision -> Servo -> PASS / REJECT
```

If something goes wrong along the way, the system is meant to notice and recover instead of just freezing.

## Stack

- C++ on an ESP32, Arduino framework, built with PlatformIO
- FreeRTOS so sensors, camera, control and telemetry each run as their own task
- Python, OpenCV and TensorFlow for training the model on a PC
- TensorFlow Lite Micro to run the shrunken model on the board
- Servo, motor, IMU and an ultrasonic/IR sensor for the hardware side
- Serial telemetry so I can actually see what the board is doing

## Where it is right now

Early days. What is here is the project skeleton and my notes. I am working through it in 12 phases:

1. Get the hardware working (GPIO, PWM, I2C, serial)
2. Split it into real modules and start the state machine
3. Computer vision on the PC first
4. Train a tiny ML model
5. Get that model running on the ESP32
6. Sensor fusion
7. Autonomous state machine
8. Fault detection and recovery
9. Watchdog and reliability
10. Telemetry
11. Test and measure
12. Clean it all up

The full breakdown lives in [Docs/](Docs/), mainly [phases.md](Docs/phases.md).

## Running it

You need VS Code with the PlatformIO extension.

```bash
git clone https://github.com/Blasted-ctrl/EdgeInspect.git
cd EdgeInspect
pio run                    # build
pio run --target upload    # flash the board
pio device monitor         # watch the serial output
```

Board target is `esp32dev`. If yours is different, change it in [platformio.ini](platformio.ini).

## A note

I am writing this to learn, so it is not going to be perfect and it is not finished. If any of it is useful to you, take it.
