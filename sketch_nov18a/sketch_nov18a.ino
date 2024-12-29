#include <LiquidCrystal.h>

// LCD pins: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Button pins
const int playPauseButton = 9;
const int nextButton = 8;
const int prevButton = 10;

// Song names array
String songs[] = {"song 1", "song 2", "song 3"};
int currentSong = 0;
bool isPlaying = true; // Initial state is 'Playing'

void setup() {
  // Set button pins as input with pull-up resistors
  pinMode(playPauseButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(prevButton, INPUT_PULLUP);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Music Controller");
  delay(2000);
  updateLCD();
}

void loop() {
  // Play/Pause Button
  if (digitalRead(playPauseButton) == LOW) {
    isPlaying = !isPlaying; // Toggle between play and pause
    if (isPlaying) {
      Serial.println("Play");
      lcd.setCursor(0, 1);
      lcd.print("Playing...      ");
    } else {
      Serial.println("Pause");
      lcd.setCursor(0, 1);
      lcd.print("Paused          ");
    }
    delay(300); // Debounce delay
  }

  // Next Button
  if (digitalRead(nextButton) == LOW) {
    currentSong = (currentSong + 1) % 3; // Loop through songs
    Serial.println("Next Track");
    updateLCD();
    delay(10); // Debounce delay
  }

  // Previous Button
  if (digitalRead(prevButton) == LOW) {
    currentSong = (currentSong - 1 + 3) % 3; // Loop backward through songs
    Serial.println("Previous Track");
    updateLCD();
    delay(300); // Debounce delay
  }
}

// Function to update LCD with current song name
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Now Playing:");
  lcd.setCursor(0, 1);
  lcd.print(songs[currentSong]);
}