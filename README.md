Matrix-Project
Introduction to Robotics (3rd Year, University of Bucharest)

This repository contains the source code and documentation for the final milestone of my Matrix Project. The current implementation features a fully functional game console running "Maze Breaker," a dungeon crawler that utilizes a 16x16 virtual map, advanced menu systems with EEPROM storage, and sensor-based interaction.

Concept
Game Title: Maze Breaker Genre: Dungeon Crawler / Puzzle Description: An infinite maze game where the player navigates a dark dungeon to find the exit. The player uses a "camera" view to explore a map larger than the screen and utilizes a "magic hammer" (Ultrasonic Sensor) to break walls when trapped.

Functionality (Final Milestone)
This milestone implements the complete architecture required for the final grading:

1. LCD Menu System
Navigation: Joystick X-Axis (Up/Down) to scroll, Y-Axis (Left/Right) to adjust sliders.

Selection: Joystick Button to select an option.

Menu Items:

Start Game: Launches the main game loop with a generated level.


High Scores: Reads the top 3 scores from EEPROM.


Settings:

Enter Name: Custom text entry for high scores.

LCD Brightness: PWM control via a visual slider bar.


Matrix Brightness: LED intensity control with full-matrix visual feedback.

Sound: Toggle system audio ON/OFF.

About / How to Play: Information screens.


Feedback: Custom icons on the Matrix update dynamically as you scroll through the LCD menu.

2. Matrix Interaction (Game Mode)
The "Start Game" option launches the Maze Breaker engine:


16x16 Map Logic: The game runs on a large 16x16 logical grid, displayed on the 8x8 physical matrix using a "camera" viewport that follows the player.


Mechanics:

Movement: Joystick navigation with collision detection.

Goal: Find the blinking exit point to gain 100 points and advance to the next level.


The Hammer: Wave your hand (< 15cm) in front of the Ultrasonic Sensor to smash walls in a 3x3 radius.



Visuals: Distinct blinking patterns for the Player (Slow Blink) and the Exit (Fast Blink).

3. Hardware Integration
EEPROM: Automatically saves High Scores, Player Name, and System Settings (Brightness/Sound) so they persist after power loss.

Audio: Passive buzzer provides feedback for menu scrolling, wall breaking, and level completion (Fanfare).

Multitasking: Uses millis() for all animations and sensor readings, ensuring no blocking delays.

Picture
<img src="placeholder" alt="Final Hardware Setup" width="500"/>

Video
[![Project Video](https://img.shields.io/badge/YouTube-Watch%20Demo-red?style=for-the-badge&logo=youtube)](Placeholder)
