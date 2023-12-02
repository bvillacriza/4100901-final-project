# 4100901-final-project
This repository contains  the final project of the course computation structures. Please go to the [C4Model](Doc/C4Model.md) diagrams for more details on the functionality of the system.

## Hardware prerequisites
* The example is a digital lock system featuring an STM32L4 for controling the system, an ESP8266 for interfacing with the internet, a keypad for getting the sequences, and an OLED display for GUI, a led will be used as part of the machine user interface. See more details in the [C4Model](Doc/C4Model.md)
* The following is the pinout of the STM32:
![pinout](Doc/pinout.png)

## Firmware prerequisites
* The ESP8266 runs the esp-link [v2.2.3](https://github.com/jeelabs/esp-link/releases/tag/v2.2.3) firmware. Please follow the [serial flashing guide](https://github.com/jeelabs/esp-link/blob/master/FLASHING.md#initial-serial-flashing).
* The STM32 runs the firmware compiled from this repository using STM32CubeIDE.

## Building and Flashing
* Open the project in STM32CubeIDE.
* Compile using the current project settings.

## Functionality
* Explanation here.
* 
* The keypad: the keypad will be used as the password input, numbers one through nine, plus the letters a, b, c, and d, along with "#" and "*" will be typed as part of the password input, the keypad is based on interrupts that will be detected by the microcontroller, 
* The Debug console: the system sends password entry data, records the events in such a way that if at any time the password is entered incorrectly, a warning will be given in the debug console, if more than 5 such events are recorded in a certain range of time, the system will block the system so that no new passwords can be entered.
* SSD-GUI: this screen will show each character that is entered as a password for a short period of time, you can warn when a wrong password is ocope and when the system is unlocked, also has a menu at the beginning in which you will have the options of password entry or put the system with a screen saver, and blocks the entry of other commands or keys.

## Contact info
* Brayan Alexis Villacriz // Hamerson Joel Piarpueza 
