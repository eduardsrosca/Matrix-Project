# Matrix-Project

> **Introduction to Robotics** (3rd Year, University of Bucharest)

This repository contains the source code and documentation for the first milestone of my Matrix Project. The current implementation features a fully functional LCD menu system and an interactive "Drawing Mode" on the 8x8 LED Matrix, demonstrating control over individual LED states (On, Off, Blinking).

---

## Concept

**Planned Game Direction:**
dungeon explorer ?

---

## Functionality (Checkpoint 1)

This milestone implements the core architecture required for the final game:

### 1. LCD Menu System
* **Navigation:** Joystick `X-Axis` (Left/Right) to scroll through options.
* **Selection:** Joystick `Button` to select an option.
* **Menu Items:**
    * **Start Game:** Enters the matrix interaction mode.
    * **Settings:** (Placeholder for future implementation).
    * **About:** (Placeholder).
* **Feedback:** The LCD updates dynamically to show the current and next available option.

### 2. Matrix Interaction (Drawing Mode)
The "Start Game" option launches a drawing tool that serves as a proof of concept for led control:
* **Movement:** Use the Joystick (`X` and `Y` axes) to move a blinking cursor across the 8x8 grid.
* **Interaction:** Pressing the Joystick button cycles the current LED through 4 states:
    1. **OFF**
    2. **ON (Fixed)**
    3. **BLINK SLOW** (500ms interval)
    4. **BLINK FAST** (100ms interval)
* **Technical Feature:** Uses non-blocking timers (`millis()`) for blinking and debouncing, ensuring smooth cursor movement without `delay()`.

---

### Picture
<img src="placeholder" alt="Checkpoint 1 Hardware Setup" width="500"/>

---

## Video

[![Watch the Checkpoint 1 Demo](https://img.shields.io/badge/YouTube-Watch%20Demo-red?style=for-the-badge&logo=youtube)](PLACE_YOUR_VIDEO_LINK_HERE)

---

## Future Development (Checkpoint 2)
* **Game Logic:** Transition from the current "drawing" mode to the actual game loop (e.g., enemy spawning, player logic).
* **EEPROM:** Saving high scores and settings (LCD brightness/Sound).
* **Sound:** Adding buzzer feedback for menu navigation and game events.
