#include <LiquidCrystal.h>
#include "LedControl.h"

// lcd pin config
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// matrix pin config
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

// joystick pin config
const int xPin = A0;
const int yPin = A1;
const int swPin = A2;

// system variables
enum State {
  INTRO,
  MENU,
  GAME
};
State currentState = INTRO;

// menu variables
String menuItems[] = {"Start Game", "Settings", "About"};
int menuLength = 3;
int currentSelection = 0;
bool menuChanged = true;
unsigned long lastMenuMove = 0;
const int menuMoveInterval = 250; 

// matrix variables
byte xPos = 0;
byte yPos = 0;
unsigned long lastGameMove = 0;
const int gameMoveInterval = 150; 
// logic: 0=off, 1=on, 2=slow link, 3=fast blink
byte gridState[8][8]; 

// timers
unsigned long lastBlinkSlow = 0;
unsigned long lastBlinkFast = 0;
bool blinkStateSlow = false;
bool blinkStateFast = false;
bool cursorVisible = true;
unsigned long lastCursorBlink = 0;

// debounce
bool buttonState = HIGH;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  
  // setup joystick buton
  pinMode(swPin, INPUT_PULLUP);
  
  // Setup lcd
  lcd.begin(16, 2);
  
  // setup matrix
  lc.shutdown(0, false);
  lc.setIntensity(0, 4);
  lc.clearDisplay(0);

  // matrix initialise
  for(int i=0; i<8; i++) for(int j=0; j<8; j++) gridState[i][j] = 0;

  // intro msg
  showIntro();
}

void loop() {
  // global blinking timers
  updateBlinkTimers(); 
  
  switch (currentState) {
    case MENU:
      handleMenu();
      break;
    case GAME:
      handleGame();
      break;
  }
}

// logic

void showIntro() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Matrix Project!");
  delay(2000); 
  currentState = MENU;
  lcd.clear();
}

void handleMenu() {
  int xValue = analogRead(xPin);
  
  // menu nav
  if (millis() - lastMenuMove > menuMoveInterval) {
    if (xValue < 200) { 
      currentSelection--;
      if (currentSelection < 0) currentSelection = menuLength - 1;
      menuChanged = true;
      lastMenuMove = millis();
    }
    if (xValue > 800) {
      currentSelection++;
      if (currentSelection >= menuLength) currentSelection = 0;
      menuChanged = true;
      lastMenuMove = millis();
    }
  }

  if (menuChanged) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("> " + menuItems[currentSelection]);
    lcd.setCursor(0, 1);
    int nextItem = (currentSelection + 1) % menuLength;
    lcd.print("  " + menuItems[nextItem]);
    menuChanged = false;
  }

  // button select
  if (readButton()) {
    if (currentSelection == 0) { // start game selected
      currentState = GAME;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mode: Drawing");
      lcd.setCursor(0, 1);
      lcd.print("Press to paint");
      lc.clearDisplay(0);
    }
    // settings will be implemented here
  }
}

void handleGame() {
  if (millis() - lastGameMove > gameMoveInterval) {
    int xValue = analogRead(xPin);
    int yValue = analogRead(yPin);
    
    // x axis logic
    if (xValue < 200) {
      if (xPos < 7) xPos++; else xPos = 0;
    }
    if (xValue > 800) {
      if (xPos > 0) xPos--; else xPos = 7;
    }
    
    // y axis logic
    if (yValue > 800) { 
      if (yPos < 7) yPos++; else yPos = 0;
    }
    if (yValue < 200) {
      if (yPos > 0) yPos--; else yPos = 7;
    }
    
    lastGameMove = millis();
  }

  if (readButton()) {
    // state cycle: 0 -> 1 -> 2 -> 3 -> 0
    gridState[xPos][yPos]++;
    if (gridState[xPos][yPos] > 3) gridState[xPos][yPos] = 0;
  }

  renderMatrix();
}

bool readButton() {
  int reading = digitalRead(swPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  bool pressed = false;
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        pressed = true;
      }
    }
  }
  lastButtonState = reading;
  return pressed;
}

void updateBlinkTimers() {
  if (millis() - lastBlinkSlow > 500) { // slow blink - 500ms
    lastBlinkSlow = millis();
    blinkStateSlow = !blinkStateSlow;
  }
  if (millis() - lastBlinkFast > 100) { // fast blink - 100ms
    lastBlinkFast = millis();
    blinkStateFast = !blinkStateFast;
  }
  if (millis() - lastCursorBlink > 150) { // nav blink
    lastCursorBlink = millis();
    cursorVisible = !cursorVisible;
  }
}

void renderMatrix() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      bool ledOn = false;
      
      switch (gridState[row][col]) {
        case 0: ledOn = false; break;            // off
        case 1: ledOn = true; break;             // on
        case 2: ledOn = blinkStateSlow; break;   // slow blink
        case 3: ledOn = blinkStateFast; break;   // fast blink
      }

      if (row == xPos && col == yPos) {
        ledOn = cursorVisible;
      }

      lc.setLed(0, row, col, ledOn);
    }
  }
}