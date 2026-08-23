# Tech Stack
C++	Main ESP32 firmware and system logic
ESP32	The actual embedded computer running the machine
Arduino framework	Makes it easier to program the ESP32 and interface with hardware
FreeRTOS	Separate tasks such as sensors, camera, control, and telemetry
OpenCV	Image preprocessing/computer vision
Python	Train and evaluate the ML model on your computer
TensorFlow / TensorFlow Lite Micro	Train → shrink → run the ML model on the ESP32
IMU	Detect vibration/movement
Ultrasonic/IR sensors	Detect object position/distance
Servo	Physically sort/reject an object
Motor	Move the inspection platform
Git/GitHub	Version control and portfolio
Serial telemetry	See what the ESP32 is doing while it runs