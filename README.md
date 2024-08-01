# _Waveshare 2.9" ePaper Example_
This code is an example from Waveshare for ESP32 for the first gen 2.9" ePaper display.
I have not tested it with later versions.
Originally it could only compile in Arduino IDE,
there is a INO file here.
I have fixed the code to also compile in VS Code with ESP-IDF APIs. 
The display uses SPI connections, but the software does not use SPI API, instead it implements
SPI by bit-banging (toggling CLK, CS, MOSI and DC lines as appropriate).
Evidently timing is not crucial for ePaper displays.

## How to build
I am using ESP-IDF v5.2.1 in Visual Studio Code. I have run this code on both ESP32s3 and ESP32c6.
This project currently does not use menuconfig.
Edit DEV_Config.h to set the GPIO pins that you use.
In VS Code remember to choose the COM port and the ESP32 type, e.g., esp32s3.
If you have a different Waveshare ePaper, it will probably work if you change the width and height.
Other models may have different commands.

## Project folder contents

The project contains one source file in C language [main.cpp](main/main.cpp). The file is located in folder [main](main).
The Chinese font files (Font12CN.c and Font24CN.c) are provided by Waveshare for demonstration and obviously are not
a complete Chinese character set!

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of some files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.cpp
│   └── epd2in9-demo.ino	:Project file for Arduino IDE
└── README.md                  This is the file you are currently reading
```
