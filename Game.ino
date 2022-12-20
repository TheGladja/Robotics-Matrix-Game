#include <LiquidCrystal.h>
#include <LedControl.h>
#include <EEPROM.h>

//for the intro song
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0
// change this to make the song slower or faster
int tempo = 220;
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  // Nokia Ringtone
  // Score available at https://musescore.com/user/29944637/scores/5266155

  NOTE_E5,
  8,
  NOTE_D5,
  8,
  NOTE_FS4,
  4,
  NOTE_GS4,
  4,
  NOTE_CS5,
  8,
  NOTE_B4,
  8,
  NOTE_D4,
  4,
  NOTE_E4,
  4,
  NOTE_B4,
  8,
  NOTE_A4,
  8,
  NOTE_CS4,
  4,
  NOTE_E4,
  4,
  NOTE_A4,
  2,
};
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

const int rowGameOver = 8;
const int colGameOver = 90;

const PROGMEM bool gameOverMessage[rowGameOver][colGameOver] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

const byte buzzerPin = A2;

const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);  //DIN, CLK, LOAD, No. DRIVER
byte matrixBrightness = 15;
byte snake[matrixSize] = { 0x7F, 0x41, 0xCF, 0x88, 0x88, 0x82, 0x85, 0x02 };
byte startGame[matrixSize] = { 0x38, 0x44, 0x88, 0x91, 0x88, 0x44, 0x38, 0x00 };
byte highscore[matrixSize] = { 0x1C, 0x3E, 0x7F, 0x49, 0x7F, 0x63, 0x7F, 0x55 };
byte settings[matrixSize] = { 0x3C, 0x7E, 0x7E, 0x3C, 0x18, 0x18, 0x18, 0x18 };
byte about[matrixSize] = { 0xFF, 0x81, 0xA5, 0x81, 0xBD, 0xBD, 0x81, 0xFF };
byte howToPlay[matrixSize] = { 0x30, 0x30, 0x1C, 0x7A, 0x38, 0x3C, 0x3E, 0x30 };
byte resetHighscore[matrixSize] = { 0x00, 0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x00 };

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte intensity = 3;

const int pinSW = 2;  // digital pin connected to switch output
const int pinX = A0;  // A0 - analog pin connected to X output
const int pinY = A1;  // A1 - analog pin connected to Y output

byte buttonValue = LOW;
int xValue = 0;
int yValue = 0;
bool joyMoved = false;
bool brightnessJoyMoved = false;
bool modifyLetterJoyMoved = false;
const int minThreshold = 400;
const int maxThreshold = 600;
const int menuDisplayNumber = 6;
const int settingsDisplayNumber = 3;
const int levelDisplayNumber = 3;
const int rankDisplayNumber = 5;
int currentMenuDisplay = 0;
int currentSettingsDisplay = 0;
int currentLevelDisplay = 0;
int currentRankDisplay = 0;
String menuDisplay[menuDisplayNumber] = { "1. Start Game", "2. Highscore", "3. Settings", "4. About", "5. How To Play", "6. Reset Score" };
String settingsMenuDisplay[settingsDisplayNumber] = { "Led Shine:", "Matrix Shine:", "Sound:" };
String levelDisplay[levelDisplayNumber] = { " EASY ", "MEDIUM", " HARD " };
String rankDisplay[rankDisplayNumber] = { "1st.", "2nd.", "3rd.", "4th.", "5th." };
bool cursorPosition = false;
String newPlayer = "";
int newScore = 0;
String emptyString = "";

char* introText = "Hello and Welcome to the amazing Cozy Snake Game!!! Press the button to enter menu...                ";
int introTextLineNumber = 1;
char* aboutText = "Github link: https://github.com/TheGladja, Creator name: Cruceanu Calin, Game name: The Cozy Snake                ";
int aboutTextLineNumber = 1;
char* howToPlayText = "Random food(dots) will spawn on the playground. Use the joystick to gather as much food as you can in 1 minute in order to beat the highscore. Good luck fellow gamer and may the force be with you. Hurry up, you don't have much time...                ";
int howToPlayTextLineNumber = 1;
const int defaultTextCursor = 0;
int scrollingTextCursor = 0;

//for the readButton function
int buttonStatePrevious = LOW;
unsigned long minButtonLongPressDuration = 3000;
unsigned long buttonLongPressMillis;
bool buttonStateLongPress = false;
const int intervalButton = 200;
unsigned long previousButtonMillis;
unsigned long buttonPressDuration;
unsigned long currentMillis;
unsigned long previousTime = 0;
const int scrollTextTime = 400;

const int alphabetLetterNumber = 25;
int currentEnterNameLetter = 0;
const int playerNameLetterNumber = 6;
int enterNameLetters[playerNameLetterNumber] = { 0, 0, 0, 0, 0, 0 };
char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int enterNameLeftLimit = 9;
const int enterNameRightLimit = 14;
int enterNameArrowPosition = 9;
int menuCursor = 1;
bool introduction = true;
bool menu = false;
bool aboutDisplay = false;
bool howToPlayDisplay = false;
bool settingsDisplay = false;
bool resetScoreDisplay = false;
bool highscoreDisplay = false;
bool startGameDisplay = false;
bool enterUserNameDisplay = true;
bool enterLevelDisplay = false;
int lcdShine = 5;
const int lcdShineStep = 50;
int matrixShine = 5;
const int matrixShineStep = 3;
bool sound = true;
bool resetScore = false;
bool gameDisplay = false;

int playerScore;
String playerName;
const int eepromLcdShine = 1;
const int eepromMatrixShine = 2;
const int eepromSound = 3;
const int eepromScoreStart = 4;
const int eepromScoreEnd = 8;
const int eepromNameStep = 6;
const int eepromNameStart = 9;
int letterContor = 0;
const int eepromNameEnd = 38;
int previousScore;
int scoreToMap;
int letterToMap;

//for the game
int randomCol;
int randomRow;
unsigned long prevTimeGame = 0;
bool food = true;
int dotRowPosition = 0;
int dotColPosition = 0;
const int blinkTime = 300;
bool ledPower = true;
int deleteDotPosition = 0;
const int matrixDotNumber = 45;
int rowSnakePosition[matrixDotNumber] = { 0 };
int colSnakePosition[matrixDotNumber] = { 0 };
bool up = false;
bool down = false;
bool right = false;
bool left = false;
bool endGame = false;
const int easySpeed = 300;
const int hardSpeed = 200;
unsigned long previousSnakeTime = 0;
bool easyLevel = false;
bool mediumLevel = false;
bool hardLevel = false;
const int matrixMessageSpeed = 5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false);  // turn off power saving, enables display
  lc.clearDisplay(0);     // clear screen

  lcd.begin(16, 2);
  pinMode(intensity, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP);

  sound = EEPROM.read(eepromSound);
  if (sound) {
    introSong();
  }

  Serial.begin(9600);
}

void loop() {
  if (introduction) {
    displayIntro();
  } else if (menu) {
    displayMenu();
  } else if (aboutDisplay) {
    aboutMenu();
  } else if (howToPlayDisplay) {
    howToPlayMenu();
  } else if (settingsDisplay) {
    settingsMenu();
  } else if (resetScoreDisplay) {
    resetScoreMenu();
  } else if (highscoreDisplay) {
    highscoreMenu();
  } else if (startGameDisplay) {
    startGameMenu();
  }
  writeIntensityAndUpdateEEPROM();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Snake Game -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void snakeGame() {
  //for displaying the score and time
  lcd.setCursor(0, 0);
  lcd.print("Score:");
  lcd.setCursor(7, 0);
  lcd.print(newScore);
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(6, 1);
  lcd.print((millis() - prevTimeGame) / 1000);

  generateFood();
  moveDot();
  if (easyLevel || mediumLevel) {
    snakeSpeed(easySpeed);
  } else if (hardLevel) {
    snakeSpeed(hardSpeed);
  }
  getPoints();
  returnToMenu();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Snake movement -------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void snakeSpeed(int speed) {
  if (millis() - previousSnakeTime >= speed) {
    if (up) {
      deleteLastDot();
      if (dotRowPosition > 0) {
        dotRowPosition--;
      } else {
        dotRowPosition = matrixSize - 1;
      }
      rowSnakePosition[0] = dotRowPosition;
    } else if (down) {
      deleteLastDot();
      if (dotRowPosition < matrixSize - 1) {
        dotRowPosition++;
      } else {
        dotRowPosition = 0;
      }
      rowSnakePosition[0] = dotRowPosition;
    } else if (right) {
      deleteLastDot();
      if (dotColPosition < matrixSize - 1) {
        dotColPosition++;
      } else {
        dotColPosition = 0;
      }
      colSnakePosition[0] = dotColPosition;
    } else if (left) {
      deleteLastDot();
      if (dotColPosition > 0) {
        dotColPosition--;
      } else {
        dotColPosition = matrixSize - 1;
      }
      colSnakePosition[0] = dotColPosition;
    }
    previousSnakeTime = millis();
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Food generator -------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void generateFood() {
  if (food) {
    if (easyLevel) {
      randomRow = random(0, 8);
      randomCol = random(0, 8);
    } else if (mediumLevel || hardLevel) {
      randomRow = random(1, 7);
      randomCol = random(1, 7);
    }
    food = false;
  }
  for (int i = 0; i <= deleteDotPosition; i++) {
    if (randomRow == rowSnakePosition[i] && randomCol == colSnakePosition[i]) {
      food = true;
    } else {
      if (millis() - previousTime >= blinkTime) {
        lc.setLed(0, randomRow, randomCol, ledPower);
        if (ledPower) {
          ledPower = false;
        } else {
          ledPower = true;
        }
        previousTime = millis();
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Update new score -----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void getPoints() {
  if (dotRowPosition == randomRow && dotColPosition == randomCol) {
    if (sound) {
      tone(buzzerPin, 6000, 20);
    }
    newScore++;
    food = true;
    deleteDotPosition++;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Change snake direction -----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void moveDot() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (mediumLevel || hardLevel) {
    for (int i = 0; i < matrixSize; i++) {
      lc.setLed(0, 0, i, true);
      lc.setLed(0, i, 0, true);
      lc.setLed(0, matrixSize - 1, i, true);
      lc.setLed(0, i, matrixSize - 1, true);
    }
  }

  //move up
  if (yValue < minThreshold && joyMoved == false) {
    if (!down) {
      right = false;
      left = false;
      up = true;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    joyMoved = true;
  }

  //move down
  if (yValue > maxThreshold && joyMoved == false) {
    if (!up) {
      right = false;
      left = false;
      down = true;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    joyMoved = true;
  }

  //move right
  if (xValue < minThreshold && joyMoved == false) {
    if (!left) {
      up = false;
      down = false;
      right = true;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    joyMoved = true;
  }

  //move left
  if (xValue > maxThreshold && joyMoved == false) {
    if (!right) {
      up = false;
      down = false;
      left = true;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold && xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }

  lc.setLed(0, dotRowPosition, dotColPosition, true);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------ Delete snake's tail --------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void deleteLastDot() {
  lc.setLed(0, rowSnakePosition[deleteDotPosition], colSnakePosition[deleteDotPosition], false);
  for (int i = deleteDotPosition; i > 0; i--) {
    rowSnakePosition[i] = rowSnakePosition[i - 1];
    colSnakePosition[i] = colSnakePosition[i - 1];
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Introduction -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayIntro() {
  displayIntroFigure();
  lcd.setCursor(1, 0);
  lcd.print("The Cozy Snake");
  scrollingMessage(introText, introTextLineNumber);
  readIntroductionButton();
}

void displayIntroFigure() {
  printByte(snake);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Menu -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayMenu() {
  displayAnimation();

  yValue = analogRead(pinY);

  //the star position
  if (cursorPosition == false) {
    menuCursor = currentMenuDisplay + 1;
    lcd.setCursor(15, 1);
    lcd.print("*");
  } else {
    menuCursor = currentMenuDisplay + 2;
    if (currentMenuDisplay == menuDisplayNumber - 1) {
      menuCursor = 1;
    }
    lcd.setCursor(15, 0);
    lcd.print("*");
  }

  lcd.setCursor(0, 1);
  lcd.print(menuDisplay[currentMenuDisplay]);
  lcd.setCursor(0, 0);

  if (currentMenuDisplay == menuDisplayNumber - 1) {
    lcd.print(menuDisplay[0]);
  } else {
    lcd.print(menuDisplay[currentMenuDisplay + 1]);
  }

  //move up
  if (yValue < minThreshold && joyMoved == false) {
    if (cursorPosition == false) {
      cursorPosition = true;
    } else {
      if (currentMenuDisplay < menuDisplayNumber - 1) {
        currentMenuDisplay++;
      } else {
        currentMenuDisplay = 0;
      }
      cursorPosition = false;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    lc.clearDisplay(0);
    joyMoved = true;
  }

  //move down
  if (yValue > maxThreshold && joyMoved == false) {
    if (cursorPosition == true) {
      cursorPosition = false;
    } else {
      if (currentMenuDisplay > 0) {
        currentMenuDisplay--;
      } else {
        currentMenuDisplay = 4;
      }
      cursorPosition = true;
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    lc.clearDisplay(0);
    joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }
  readMenuButton();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------- Start Game menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void startGameMenu() {
  if (enterUserNameDisplay) {
    enterUserName();
  } else if (enterLevelDisplay) {
    enterLevel();
  } else if (gameDisplay) {
    snakeGame();
  }
  readMenuButton();
}

void enterLevel() {
  xValue = analogRead(pinX);

  //for the arrows
  if (currentLevelDisplay == 0) {
    lcd.setCursor(15, 0);
    lcd.print(">");
    hardLevel = false;
    mediumLevel = false;
    easyLevel = true;
  } else if (currentLevelDisplay == levelDisplayNumber - 1) {
    lcd.setCursor(0, 0);
    lcd.print("<");
    mediumLevel = false;
    easyLevel = false;
    hardLevel = true;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");
    easyLevel = false;
    hardLevel = false;
    mediumLevel = true;
  }

  //display the image
  lcd.setCursor(3, 0);
  lcd.print("Difficulty");
  lcd.setCursor(5, 1);
  lcd.print(levelDisplay[currentLevelDisplay]);

  //move left
  if (xValue < minThreshold && joyMoved == false) {
    if (currentLevelDisplay < levelDisplayNumber - 1) {
      currentLevelDisplay++;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //move right
  if (xValue > maxThreshold && joyMoved == false) {
    if (currentLevelDisplay > 0) {
      currentLevelDisplay--;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //reset joystick
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }
}

void enterUserName() {
  lcd.setCursor(enterNameArrowPosition, 0);
  lcd.print("v");
  lcd.setCursor(0, 1);
  lcd.print("Name:");
  lcd.setCursor(8, 1);
  lcd.print(">");
  lcd.setCursor(15, 1);
  lcd.print("<");

  moveNameArrow();
  displayUserName();
  modifyLetter();
}

void modifyLetter() {
  yValue = analogRead(pinY);

  //move up
  if (yValue < minThreshold && modifyLetterJoyMoved == false) {
    if (enterNameLetters[currentEnterNameLetter] < alphabetLetterNumber) {
      enterNameLetters[currentEnterNameLetter]++;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    modifyLetterJoyMoved = true;
  }

  //move down
  if (yValue > maxThreshold && modifyLetterJoyMoved == false) {
    if (enterNameLetters[currentEnterNameLetter] > 0) {
      enterNameLetters[currentEnterNameLetter]--;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    modifyLetterJoyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    modifyLetterJoyMoved = false;
  }
}

void displayUserName() {
  lcd.setCursor(9, 1);
  lcd.print(alphabet[enterNameLetters[0]]);
  lcd.setCursor(10, 1);
  lcd.print(alphabet[enterNameLetters[1]]);
  lcd.setCursor(11, 1);
  lcd.print(alphabet[enterNameLetters[2]]);
  lcd.setCursor(12, 1);
  lcd.print(alphabet[enterNameLetters[3]]);
  lcd.setCursor(13, 1);
  lcd.print(alphabet[enterNameLetters[4]]);
  lcd.setCursor(14, 1);
  lcd.print(alphabet[enterNameLetters[5]]);
}

void moveNameArrow() {
  xValue = analogRead(pinX);

  //move left
  if (xValue < minThreshold && joyMoved == false) {
    if (enterNameArrowPosition < enterNameRightLimit) {
      currentEnterNameLetter++;
      enterNameArrowPosition++;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //move right
  if (xValue > maxThreshold && joyMoved == false) {
    if (enterNameArrowPosition > enterNameLeftLimit) {
      currentEnterNameLetter--;
      enterNameArrowPosition--;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //reset joystick
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Settings menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void settingsMenu() {
  xValue = analogRead(pinX);

  //for the arrows
  if (currentSettingsDisplay == 0) {
    lcd.setCursor(15, 0);
    lcd.print(">");
  } else if (currentSettingsDisplay == settingsDisplayNumber - 1) {
    lcd.setCursor(0, 0);
    lcd.print("<");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");
  }

  //display the menu settings static variables
  if (currentSettingsDisplay == 0) {
    lcd.setCursor(13, 1);
    lcd.print(lcdShine);
    lcd.setCursor(14, 1);
    lcd.print("/5");
  } else if (currentSettingsDisplay == 1) {
    lcd.setCursor(13, 1);
    lcd.print(matrixShine);
    lcd.setCursor(14, 1);
    lcd.print("/5");
  } else if (currentSettingsDisplay == 2) {
    lcd.setCursor(12, 1);
    if (sound) {
      lcd.print("on");
    } else {
      lcd.print("off");
    }
  }

  //display the image we want to see
  lcd.setCursor(4, 0);
  lcd.print("Settings");
  lcd.setCursor(0, 1);
  lcd.print(settingsMenuDisplay[currentSettingsDisplay]);

  //move left
  if (xValue < minThreshold && joyMoved == false) {
    if (currentSettingsDisplay < settingsDisplayNumber - 1) {
      currentSettingsDisplay++;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //move right
  if (xValue > maxThreshold && joyMoved == false) {
    if (currentSettingsDisplay > 0) {
      currentSettingsDisplay--;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //reset joystick
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }

  modifyBrightnessAndSound();
  readMenuButton();
}

void modifyBrightnessAndSound() {
  yValue = analogRead(pinY);

  //move up
  if (yValue < minThreshold && brightnessJoyMoved == false) {
    if (currentSettingsDisplay == 0) {
      if (lcdShine < 5) {
        lcdShine++;
        EEPROM.write(eepromLcdShine, lcdShine);
      }
    } else if (currentSettingsDisplay == 1) {
      if (matrixShine < 5) {
        matrixShine++;
        EEPROM.write(eepromMatrixShine, matrixShine);
      }
    } else if (currentSettingsDisplay == 2) {
      EEPROM.write(eepromSound, 1);
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    brightnessJoyMoved = true;
  }

  //move down
  if (yValue > maxThreshold && brightnessJoyMoved == false) {
    if (currentSettingsDisplay == 0) {
      if (lcdShine > 0) {
        lcdShine--;
        EEPROM.write(eepromLcdShine, lcdShine);
      }
    } else if (currentSettingsDisplay == 1) {
      if (matrixShine > 0) {
        matrixShine--;
        EEPROM.write(eepromMatrixShine, matrixShine);
      }
    } else if (currentSettingsDisplay == 2) {
      EEPROM.write(eepromSound, 0);
    }

    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    brightnessJoyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    brightnessJoyMoved = false;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------- How To Play menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void howToPlayMenu() {
  lcd.setCursor(2, 0);
  lcd.print("How to play");
  scrollingMessage(howToPlayText, howToPlayTextLineNumber);
  readMenuButton();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------- About menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void aboutMenu() {
  lcd.setCursor(5, 0);
  lcd.print("About");
  scrollingMessage(aboutText, aboutTextLineNumber);
  readMenuButton();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------- Reset Score menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void resetScoreMenu() {
  yValue = analogRead(pinY);

  lcd.setCursor(5, 0);
  lcd.print("Reset");
  lcd.setCursor(5, 1);
  lcd.print("Cancel");

  //print the arrow
  if (resetScore) {
    lcd.setCursor(4, 0);
    lcd.print(">");
  } else {
    lcd.setCursor(4, 1);
    lcd.print(">");
  }

  //move up
  if (yValue < minThreshold && joyMoved == false) {
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    resetScore = true;
    joyMoved = true;
  }

  //move down
  if (yValue > maxThreshold && joyMoved == false) {
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    resetScore = false;
    joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }

  readMenuButton();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------- Highscore menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void highscoreMenu() {
  xValue = analogRead(pinX);

  //for the arrows
  if (currentRankDisplay == 0) {
    lcd.setCursor(15, 0);
    lcd.print(">");
  } else if (currentRankDisplay == rankDisplayNumber - 1) {
    lcd.setCursor(0, 0);
    lcd.print("<");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("<");
    lcd.setCursor(15, 0);
    lcd.print(">");
  }

  //display the image we want to see
  lcd.setCursor(3, 0);
  lcd.print("Highscore");
  lcd.setCursor(0, 1);
  lcd.print(rankDisplay[currentRankDisplay]);
  lcd.setCursor(5, 1);
  lcd.print(playerName);
  lcd.setCursor(12, 1);
  lcd.print(":");
  lcd.setCursor(14, 1);
  lcd.print(playerScore);

  //move left
  if (xValue < minThreshold && joyMoved == false) {
    if (currentRankDisplay < rankDisplayNumber - 1) {
      currentRankDisplay++;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //move right
  if (xValue > maxThreshold && joyMoved == false) {
    if (currentRankDisplay > 0) {
      currentRankDisplay--;
    }
    if (sound) {
      tone(buzzerPin, 3000, 5);
    }
    lcd.clear();
    joyMoved = true;
  }

  //reset joystick
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }

  modifyBrightnessAndSound();
  readMenuButton();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------- Other features for common use -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------- Displays the matrix picture -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printByte(byte character[]) {
  int i = 0;
  for (i = 0; i < matrixSize; i++) {
    lc.setRow(0, i, character[i]);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------- Writes intensity for matrix and lcd and updates the eeprom variables -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void writeIntensityAndUpdateEEPROM() {
  playerName = emptyString;
  //getting the player name from eeprom
  for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
    playerName.concat(char(EEPROM.read(i)));
  }

  playerScore = EEPROM.read(eepromScoreStart + currentRankDisplay);
  lcdShine = EEPROM.read(eepromLcdShine);
  matrixShine = EEPROM.read(eepromMatrixShine);
  sound = EEPROM.read(eepromSound);

  analogWrite(intensity, (lcdShine * lcdShineStep));
  lc.setIntensity(0, (matrixShine * matrixShineStep));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------- For the scrolling message -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void scrollingMessage(char* Text, int TextLineNumber) {
  if (millis() - previousTime >= scrollTextTime) {
    int lengthOfText = strlen(Text);

    if (scrollingTextCursor == lengthOfText - 1) {
      scrollingTextCursor = 0;
    }
    lcd.setCursor(0, TextLineNumber);
    if (scrollingTextCursor < lengthOfText - 16) {
      for (int i = scrollingTextCursor; i < scrollingTextCursor + 16; i++) {
        lcd.print(Text[i]);
      }
    } else {
      for (int i = scrollingTextCursor; i < lengthOfText; i++) {
        lcd.print(Text[i]);
      }
      for (int i = 0; i <= 16 - (lengthOfText - scrollingTextCursor); i++) {
        lcd.print(Text[i]);
      }
    }
    scrollingTextCursor++;
    previousTime = millis();
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------ Displays the matrix picture for each menu part -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayAnimation() {
  if (menuCursor == 1) {
    printByte(startGame);
  } else if (menuCursor == 2) {
    printByte(highscore);
  } else if (menuCursor == 3) {
    printByte(settings);
  } else if (menuCursor == 4) {
    printByte(about);
  } else if (menuCursor == 5) {
    printByte(howToPlay);
  } else {
    printByte(resetHighscore);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------- Reads the introduction button press -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void readIntroductionButton() {
  currentMillis = millis();

  if (currentMillis - previousButtonMillis > intervalButton) {
    buttonValue = digitalRead(pinSW);
    buttonValue = !buttonValue;
    if (buttonValue == HIGH) {
      if (sound) {
        tone(buzzerPin, 1000, 5);
      }
      introduction = false;
      menu = true;
      lc.clearDisplay(0);
      lcd.clear();
    }
    previousButtonMillis = currentMillis;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------- For each button press while in menu -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void readMenuButton() {
  currentMillis = millis();

  if (currentMillis - previousButtonMillis > intervalButton) {
    buttonValue = digitalRead(pinSW);
    buttonValue = !buttonValue;

    if (buttonValue == HIGH && buttonStatePrevious == LOW && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = HIGH;
    }

    buttonPressDuration = currentMillis - buttonLongPressMillis;

    //for the long pressing button
    if (buttonValue == HIGH && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      if (sound) {
        tone(buzzerPin, 3000, 20);
      }

      if (menuCursor == 1) {
        if (enterUserNameDisplay) {
          enterUserNameDisplay = false;
          enterLevelDisplay = true;
          lcd.clear();
        }
      }

      buttonStateLongPress = true;
    }

    if (buttonValue == LOW && buttonStatePrevious == HIGH) {
      buttonStatePrevious = LOW;
      buttonStateLongPress = false;

      //for the short pressing button
      if (!buttonStateLongPress && buttonPressDuration < minButtonLongPressDuration) {
        if (sound) {
          tone(buzzerPin, 1000, 5);
        }
        if (menuCursor == 1) {
          if (startGameDisplay == false) {
            menu = false;
            startGameDisplay = true;
            lcd.clear();
          } else if (enterLevelDisplay) {
            if (easyLevel) {
              dotRowPosition = 0;
              dotColPosition = 0;
            } else if (mediumLevel || hardLevel) {
              dotRowPosition = 1;
              dotColPosition = 1;
              rowSnakePosition[0] = 1;
              colSnakePosition[0] = 1;
            }

            up = false;
            down = false;
            right = false;
            left = false;
            endGame = false;

            enterLevelDisplay = false;
            gameDisplay = true;
            prevTimeGame = millis();
            lc.clearDisplay(0);
            lcd.clear();
          }
        }
        if (menuCursor == 2) {
          if (highscoreDisplay == false) {
            menu = false;
            highscoreDisplay = true;
            lcd.clear();
          } else {
            menu = true;
            highscoreDisplay = false;
            lcd.clear();
          }
        }
        if (menuCursor == 3) {
          if (settingsDisplay == false) {
            menu = false;
            settingsDisplay = true;
            lcd.clear();
          } else {
            menu = true;
            settingsDisplay = false;
            lcd.clear();
          }
        }
        if (menuCursor == 4) {
          if (aboutDisplay == false) {
            menu = false;
            aboutDisplay = true;
            scrollingTextCursor = defaultTextCursor;
            lcd.clear();
          } else {
            menu = true;
            aboutDisplay = false;
            lcd.clear();
          }
        }
        if (menuCursor == 5) {
          if (howToPlayDisplay == false) {
            menu = false;
            howToPlayDisplay = true;
            scrollingTextCursor = defaultTextCursor;
            lcd.clear();
          } else {
            menu = true;
            howToPlayDisplay = false;
            lcd.clear();
          }
        }
        if (menuCursor == 6) {
          if (resetScoreDisplay == false) {
            menu = false;
            resetScoreDisplay = true;
            lcd.clear();
          } else {
            if (resetScore) {
              for (int i = eepromScoreStart; i <= eepromScoreEnd; i++) {
                EEPROM.write(i, 0);
              }
            }
            menu = true;
            resetScoreDisplay = false;
            lcd.clear();
          }
        }
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------- When the game ends you will be back to menu  --------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void returnToMenu() {

  for (int i = 1; i <= deleteDotPosition; i++) {
    if (rowSnakePosition[0] == rowSnakePosition[i] && colSnakePosition[0] == colSnakePosition[i]) {
      endGame = true;
    }
  }

  if (mediumLevel || hardLevel) {
    if (rowSnakePosition[0] == 0 || rowSnakePosition[0] == (matrixSize - 1) || colSnakePosition[0] == 0 || colSnakePosition[0] == (matrixSize - 1)) {
      endGame = true;
    }
  }

  if (endGame) {
    //display final lcd message
    if (newScore > EEPROM.read(eepromScoreStart)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Congratulations!");
      lcd.setCursor(0, 1);
      lcd.print("New Highscore!!!");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Better luck");
      lcd.setCursor(0, 1);
      lcd.print("Next time :(");
    }

    displayScrollingMatrixMessage();

    //update highscore if necessary
    if (newScore > EEPROM.read(eepromScoreStart)) {
      currentRankDisplay = 0;
      letterContor = 0;

      //move the score down
      scoreToMap = EEPROM.read(eepromScoreStart);
      for (int i = eepromScoreStart + 1; i <= eepromScoreEnd; i++) {
        previousScore = EEPROM.read(i);
        EEPROM.write(i, scoreToMap);
        scoreToMap = previousScore;
      }
      EEPROM.write(eepromScoreStart, newScore);

      //move the other players down
      for (int i = eepromNameEnd; i >= eepromNameStep + eepromNameStart; i--) {
        letterToMap = EEPROM.read(i - eepromNameStep);
        EEPROM.write(i, letterToMap);
      }

      //write the new player name to eeprom
      for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
        EEPROM.write(i, alphabet[enterNameLetters[letterContor]]);
        letterContor++;
      }
    } else if (newScore > EEPROM.read(eepromScoreStart + 1)) {
      currentRankDisplay = 1;
      letterContor = 0;

      //move the score down
      scoreToMap = EEPROM.read(eepromScoreStart + 1);
      for (int i = eepromScoreStart + 2; i <= eepromScoreEnd; i++) {
        previousScore = EEPROM.read(i);
        EEPROM.write(i, scoreToMap);
        scoreToMap = previousScore;
      }
      EEPROM.write((eepromScoreStart + 1), newScore);

      //move the other players down
      for (int i = eepromNameEnd; i >= (eepromNameStep * (currentRankDisplay + 1)) + eepromNameStart; i--) {
        letterToMap = EEPROM.read(i - eepromNameStep);
        EEPROM.write(i, letterToMap);
      }

      // write the new player name to eeprom
      for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
        EEPROM.write(i, alphabet[enterNameLetters[letterContor]]);
        letterContor++;
      }
    } else if (newScore > EEPROM.read(eepromScoreStart + 2)) {
      currentRankDisplay = 2;
      letterContor = 0;

      //move the score down
      scoreToMap = EEPROM.read(eepromScoreStart + 2);
      for (int i = eepromScoreStart + 3; i <= eepromScoreEnd; i++) {
        previousScore = EEPROM.read(i);
        EEPROM.write(i, scoreToMap);
        scoreToMap = previousScore;
      }
      EEPROM.write((eepromScoreStart + 2), newScore);

      //move the other players down
      for (int i = eepromNameEnd; i >= (eepromNameStep * (currentRankDisplay + 1)) + eepromNameStart; i--) {
        letterToMap = EEPROM.read(i - eepromNameStep);
        EEPROM.write(i, letterToMap);
      }

      // write the new player name to eeprom
      for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
        EEPROM.write(i, alphabet[enterNameLetters[letterContor]]);
        letterContor++;
      }
    } else if (newScore > EEPROM.read(eepromScoreStart + 3)) {
      currentRankDisplay = 3;
      letterContor = 0;

      //move the score down
      scoreToMap = EEPROM.read(eepromScoreStart + 3);
      for (int i = eepromScoreStart + 4; i <= eepromScoreEnd; i++) {
        previousScore = EEPROM.read(i);
        EEPROM.write(i, scoreToMap);
        scoreToMap = previousScore;
      }
      EEPROM.write((eepromScoreStart + 3), newScore);

      //move the other players down
      for (int i = eepromNameEnd; i >= (eepromNameStep * (currentRankDisplay + 1)) + eepromNameStart; i--) {
        letterToMap = EEPROM.read(i - eepromNameStep);
        EEPROM.write(i, letterToMap);
      }

      // write the new player name to eeprom
      for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
        EEPROM.write(i, alphabet[enterNameLetters[letterContor]]);
        letterContor++;
      }
    } else if (newScore > EEPROM.read(eepromScoreStart + 4)) {
      currentRankDisplay = 4;
      letterContor = 0;

      EEPROM.write((eepromScoreStart + 4), newScore);

      // write the new player name to eeprom
      for (int i = eepromNameStart + (eepromNameStep * currentRankDisplay); i < eepromNameStep + (eepromNameStart + (eepromNameStep * currentRankDisplay)); i++) {
        EEPROM.write(i, alphabet[enterNameLetters[letterContor]]);
        letterContor++;
      }
    }

    //reset position arrays for snake
    for (int i = 0; i <= deleteDotPosition; i++) {
      rowSnakePosition[i] = 0;
      colSnakePosition[i] = 0;
    }

    //reset newPlayer and input name and score
    for (int i = 0; i < playerNameLetterNumber; i++) {
      enterNameLetters[i] = 0;
    }
    newPlayer = emptyString;
    newScore = 0;
    deleteDotPosition = 0;

    menu = true;
    startGameDisplay = false;
    enterUserNameDisplay = true;
    gameDisplay = false;
    food = true;
    lcd.clear();
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------- Displays the scrolling message on matrix ------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayScrollingMatrixMessage() {
  for (int i = 0; i < sizeof(gameOverMessage[0]) - (matrixSize - 1); i++) {
    for (int col = 0; col < matrixSize; col++) {
      delay(matrixMessageSpeed);
      for (int row = 0; row < matrixSize; row++) {
        lc.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col +i])));
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------- The song played in the introduction -----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void introSong() {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;  // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration * 0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}
