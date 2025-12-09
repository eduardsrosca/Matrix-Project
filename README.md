Maze Breaker: Matrix Project
Introduction to Robotics (3rd Year, University of Bucharest)

This repository contains the source code and documentation for my Matrix Project, a fully functional Arduino-based game console. The final project features "Maze Breaker," an infinite dungeon crawler where players navigate a 16x16 map using a "camera" viewport, complete with high-score tracking, adjustable settings, and gesture-based interaction.

Game Description: "Maze Breaker"
Maze Breaker is a dungeon crawler where the player must navigate a dark maze to find the blinking exit. However, the player is not helpless—using the Ultrasonic Sensor, the player can activate a "Hammer" ability to smash through walls when stuck.

Objective: Find the blinking exit point to advance to the next level.


Map System: The game runs on a logical 16x16 Grid, displayed on the physical 8x8 matrix using a smart camera system that follows the player.

Unique Mechanic: The "Hammer." Wave your hand in front of the sensor (< 15cm) to destroy walls in a 3x3 radius around the player.

Progression: Levels are generated randomly. Each victory grants 100 points and increases the difficulty.

Hardware Setup
The project uses the following components:

Arduino Uno (Microcontroller)

MAX7219 8x8 LED Matrix (Display)

LCD 1602 Display (Menu & Status)

Analog Joystick (Navigation)

HC-SR04 Ultrasonic Sensor (Gesture Control)

Passive Buzzer (Sound Effects)

Breadboard & Jumper Wires

Pin Mapping
LCD: RS=9, EN=8, D4=7, D5=A4, D6=5, D7=4

LCD Backlight: Pin 6 (PWM for brightness control)

Matrix: DIN=12, CLK=11, CS=10

Joystick: X=A0, Y=A1, SW=A2

Sensor: Trig=13, Echo=A3

Buzzer: Pin 3

Features Implemented
1. Advanced Menu System 

A comprehensive, icon-driven menu system displayed on both the LCD and the Matrix.

Start Game: Launches the main game loop.

High Scores: Displays the top score saved in non-volatile memory.

Settings: A fully interactive settings menu allowing the user to:


Enter Name: Custom 3-letter name entry for high scores.


LCD Brightness: Visual slider to adjust backlight intensity (PWM).


Matrix Brightness: Visual slider to adjust LED intensity.


Sound Control: Toggle game sounds ON/OFF.

Reset Data: Clears high scores.

About / How to Play: Informative screens regarding the project.

2. Deep System Integration

EEPROM Storage: High scores, player names, and all system settings (brightness, sound) are saved permanently and loaded on startup.


16x16 "Camera" Logic: Since the map is larger than the screen, a viewport algorithm shifts the visible area to keep the player centered.

Multitasking: The code relies entirely on millis() timers rather than delay(), allowing for smooth sensor reading, matrix animations, and joystick inputs simultaneously.

3. Audio-Visual Feedback
Sound: Distinct sounds for menu navigation, movement, wall smashing, and level completion.

Visuals:


Matrix: Custom icons for every menu item (Play, Trophy, Settings Gear, Book, etc.).

Animations: Blink effects for the player and exit; full-matrix flash when adjusting brightness.

Media
Setup Picture
(Replace this line with an image tag: <img src="placeholder" width="600">)

Video Demo
[![Watch the project here](https://img.shields.io/badge/YouTube-Watch%20Demo-red?style=for-the-badge&logo=youtube)](Placeholder)
How to Play
Power On: You will be greeted by the intro sequence.

Menu: Use the Joystick Up/Down to scroll. Press the Button to select.

In-Game:

Move: Use the Joystick to navigate the maze.

Smash: If blocked, wave your hand within 15cm of the ultrasonic sensor to break surrounding walls.

Win: Reach the blinking LED (Exit) to score points and generate a new level.

End Game: Your score accumulates as long as you keep playing. If you beat the high score, you will be prompted to save your name.

Project Details
Author: Rosca Eduard-Sebastian
Course: Introduction to Robotics, 2025-2026
