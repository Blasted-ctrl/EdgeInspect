# Run the camera and firmware

Both programs use C++. They run on different computers and have separate entry
points: the laptop uses `main()`; the ESP32 uses Arduino `setup()` and `loop()`.
Putting camera code in another file under `src/` would still compile it for the
ESP32. The laptop program therefore lives in `tools/`, outside PlatformIO's
firmware source directory.

## In Cortex

1. Open this project's folder.
2. Open `tools/camera_preview.cpp` and press **Run**. This builds a Windows
   program and opens the laptop's default webcam in **EdgeInspect - Camera**.
3. Press **Esc** or **Q** in the preview, close its window, or use Cortex's Stop
   button to stop the preview.
4. Use the hammer **Build** button to compile `src/main.cpp` for the ESP32.
   Build does not upload or run firmware on the physical board.

The local `.cortex/config.json` selects `g++` so the laptop program uses the
installed MSYS2 UCRT64 compiler and its matching OpenCV libraries. Cortex reads
OpenCV's include/link flags automatically. If cloning onto another computer,
install a matching host compiler/OpenCV package through Cortex's Libraries
settings, and select that compiler in the project build settings.

On this laptop, OpenCV's HighGUI window also needs MSYS2's optional Qt runtime.
It is now installed. If a fresh MSYS2 installation builds successfully but the
program exits immediately with `0xC0000135` (a missing DLL), install the matching
runtime in an MSYS2 terminal:

```sh
pacman -S --needed mingw-w64-ucrt-x86_64-qt6-5compat
```

The current firmware preserves the original `State` and `Object` types, starts
serial at 115200 baud, and reports that it is ready. The camera program previews
the laptop camera. Detection, PC-to-board messages and servo commands are not
implemented by this split; it does not invent classifications or move hardware.

## Camera checks

After Cortex has built the laptop executable, these commands can be used in its
Terminal. The MSYS2 UCRT64 `bin` directory must be on PATH for OpenCV's DLLs.

```powershell
$env:PATH = 'C:\msys64\ucrt64\bin;' + $env:PATH
.\.cortex\build\camera_preview.exe --check
.\.cortex\build\camera_preview.exe --camera 1
```

`--check` reads one real frame, prints its size/backend and exits. It does not
record or transmit frames. Camera failures return a nonzero exit code; they are
not reported as success. If access fails, check the selected camera index,
Windows camera privacy settings, and whether another application has the camera
open.

The original mixed sketch is preserved byte-for-byte in
`Docs/reference/camera-sketch-before-split.cpp.txt`.

## Verified on this laptop

On 2026-10-16, an isolated copy of these sources passed Cortex's ESP32 Build
action and produced `firmware.bin`. Cortex's Run action compiled the camera
program without diagnostics, displayed a real 640x480 DirectShow feed, and
exited with code 0 when its window was closed. The one-frame `--check` also
passed; `--camera -1` correctly returned usage-error code 2. No board was flashed.

The Windows preview explicitly shows its own window because Cortex hides child
console windows. Closing the last Qt window is treated as a normal exit, while
camera failures and other OpenCV exceptions remain errors.

OpenCV references: [VideoCapture](https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html)
and [HighGUI](https://docs.opencv.org/4.x/d7/dfc/group__highgui.html).
