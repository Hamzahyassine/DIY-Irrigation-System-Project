
# Project Progression

This file is a collection of notes about what I tried, learned, and want to improve as I build the project.

## August 13, 2026: Building the First Prototype

I started with an Arduino Uno, one soil-moisture sensor, and one small pump. For the water tank, I used a plastic 1-gallon water jug.

Starting with one sensor and one pump helped me understand the basic process: read the soil, make a decision, and turn on the pump. I also learned to think about tubing, water placement, and keeping the electronics away from the tank.

## Late August 2026: Expanding to Two Plants

Once the first version made sense, I added a second sensor and pump for a second plant.

I learned that each plant needed its own reading and its own pump decision. This also introduced more wiring and made power and relay behavior more important.

## September 3, 2026: Moving to the ESP32

I decided to move the project from the Uno to an ESP32 so I could use Wi-Fi and try wireless firmware updates.

I learned that changing boards means checking the pins, voltage levels, and PlatformIO settings instead of only copying the code. I also learned that a 5 V relay's power connection and control signal are separate, and that pumps need suitable external power.

I was confused about the ESP32's `VIN` pin at first. I learned that USB can make power available through VIN on many development boards, but I should check the exact board and power requirements before using it.

## Setting Up PlatformIO

I first had an `irrigation` folder containing a loose Arduino-style `.ino` file. The working `irrigation system` folder is a PlatformIO project with a different structure:

- `src/main.cpp` contains the application code.
- `platformio.ini` defines the board, framework, and upload settings.
- `.pio` contains generated build files and should not be edited.
- `.vscode` contains editor and project settings.
- `include`, `lib`, and `test` are PlatformIO locations for headers, libraries, and tests.

I learned that VS Code is the editor, while PlatformIO provides the project structure, build process, and upload tools.

## Adding Over-the-Air Updates

I added ArduinoOTA so I can upload new firmware over Wi-Fi. This will be useful because the finished system may be in an awkward place to reach with a USB cable.

I learned that the first OTA setup still needs a USB upload. After that, the ESP32 and computer need to be on the same Wi-Fi network. I also learned that Wi-Fi and OTA are related but different: Wi-Fi provides the connection, while OTA handles the firmware update.

## Learning Git

I learned that Git can keep a local history of the project. Editing a file saves it on disk, but it does not automatically create a commit.

A commit is a named snapshot. The basic workflow is:

```text
Edit files -> git add -> git commit -> optional git push
```

The commit stays local until it is pushed to GitHub. Clear commit messages help show how the project changed, for example:

```text
Migrate sensor readings from Uno pins to ESP32 ADC1 pins
Document relay power and trigger wiring
```

## Current Implementation

The current code reads both sensors every 60 seconds. It treats readings above `2500` as dry soil and runs the matching pump for one second. The ESP32 connects to Wi-Fi and supports OTA updates.

## Next Experiments

- Measure wet and dry sensor values and calibrate the threshold for each plant.
- Confirm that the relay modules trigger reliably from 3.3 V GPIO signals.
- Test the pumps with their final power supply and tubing.
- Add photos or a short demonstration video once the physical setup is stable.
- Add safety limits so a failed sensor cannot run a pump indefinitely.

