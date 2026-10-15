"""Host-side OpenCV demo for EdgeInspect: runs on your PC, not on the ESP32.

It lives in tools/ (outside src/), so PlatformIO never builds it into the
firmware. It draws a synthetic metal plate with a hole and a chipped corner,
finds its edges with Canny, and prints how many edge pixels were found plus a
small ASCII picture of them. Same program as edge_detect.cpp, in Python.
"""
import cv2
import numpy as np

size = 160
plate = np.full((size, size), 40, np.uint8)
cv2.rectangle(plate, (30, 30), (130, 130), 200, cv2.FILLED)  # the plate
cv2.circle(plate, (80, 80), 25, 40, cv2.FILLED)              # a drilled hole
cv2.rectangle(plate, (30, 30), (48, 40), 40, cv2.FILLED)     # chipped corner (the defect)

blurred = cv2.GaussianBlur(plate, (5, 5), 1.4)
edges = cv2.Canny(blurred, 50, 150)

print(f"OpenCV {cv2.__version__}")
print(f"edge pixels found: {cv2.countNonZero(edges)}\n")

# 4x4 pixels per character: '#' wherever the block contains an edge.
block = 4
for y in range(0, size, block):
    print("".join("#" if edges[y:y + block, x:x + block].any() else " " for x in range(0, size, block)))
