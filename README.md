# Robotics-Matrix-Game

 ## Homework 5 (game menu)

 ### Requirements 
 
 #### Components
 An LCD, a joystick, a buzzer, led matrix, potentiometer and a max7219 datasheet.
 
 #### Menu
 
 ##### -Intro message
 
 ##### -Start Game
 * Shown details while playing.
 * Screen(s) upon game ending with input in order to move on.
 * Informs you when highscore is achieved.
 * Enter name for highscore (if not already entered).
 
 ##### -Highscore
 At least top 5 in eeprom with name and score.
 
 ##### -Settings
 ∗ Enter name (can be somewhere else, depending on how and where you use it).
 ∗ Starting level / difficulty or something similar, depending on game logic.
 ∗ LCD contrast control (eeprom) - optional.
 ∗ LCD brightness control (eeprom).
 ∗ Matrix brightness control (eeprom). Light up the entire matrix when changing it, so you can see the actual difference.
 ∗ Sound control on/off (eeprom).
 ∗ Reset highscores button in settings.
 
 ##### -About
 Github link/user (specifcy if user!), developer name and game name.
 
 ##### -How to play
 Short and informative description.
 
 ##### -Navigation style
 Usability, intiuitive, beauty. Different ”picture” on the matrix for each menu category (hammer for settings, challice for highscore etc). Should do a small sound  when changing selected menu category etc.
 
 ##### Have fun!
 
 #### Coding task
 Coding style is of utmost importance. You must have a perfectly clean code in order to receive the maximum grade. An important coding challenge present in this task is using millis() instead of delay(). However, remember that the bulk of the grade is if the project works. Do not tend to small details unless you have the entire functionality done.
 
 ### Details
 
 #### When starting the menu you will hear the authentic Nokia sound.
 
 #### Introduction
 * The game title.
 * A short welcoming scrolling message.
 
 #### Menu (each part will have a different matrix picture)
 You will see a star in the right part of the LCD indicating the current position on the menu.
 Press the joystick button to enter each of these menu parts:
 
 ##### 1. Start game.
 
 ###### Enter player name
 You will need to enter a 6 letter user name.
 Up on the LCD screen a down arrow will indicate the current letter.
 Use the joystick up/down to change the current letter and left/right to cycle through letters.
 Long press the joystick button for 3 seconds to enter the next state.
 
 ###### Select difficulty level
 Use the joystick left/right to select a difficulty level and then press the joystick button to start the game.
 There will be arrows on the upper side of the LCD indicating the position.
 
 ##### 2. Highscore.
 Use the joystick left/right to cycle through the top 5 players.
 Press the joystick button to return to the menu.
 
 ##### 3. Settings.
 Use the joystick left/right to cycle through each setting.
 Press the joystick button to return to the menu.
 
 ###### Led shine
 Use the joystick up/down to select the LCD brightness (0 to 5).
 
 ###### Matrix shine
 Use the joystick up/down to select the matrix brightness (0 to 5).
 
 ###### Sound
 Use the joystick up/down to control the sound (on/off).
 
 ##### 4. About.
 A short scrolling message describing the creator github link, creator name and game name.
 Press the joystick button to return to the menu.
 
 ##### 5. How to play.
 A short scrolling message description about how to play the game.
 Press the joystick button to return to the menu.
 
 ##### 6. Reset score
 Use the joystick up/down to select RESET (reset the highscore the returns you to the menu) or CANCEL (return to menu).
 
 ### Image files
 #### Checkout this link
 https://www.youtube.com/watch?v=s0oF2kljLoA&list=PLASPWLXL8uFXgAFEjd-jlXm1SQpGpdLho&index=5&ab_channel=CruceanuCalin
 #### Setup photos
 ![WhatsApp Image 2022-12-09 at 13 34 55](https://user-images.githubusercontent.com/80258120/206701556-49a8d51d-342c-409e-85d0-fe3b9530755f.jpeg)
 ![WhatsApp Image 2022-12-09 at 13 34 56](https://user-images.githubusercontent.com/80258120/206701566-80867869-d0b1-402c-a5cd-710e775bdea8.jpeg) 
 ![WhatsApp Image 2022-12-09 at 13 34 56 (1)](https://user-images.githubusercontent.com/80258120/206701589-091c85c1-54e3-4ebf-ac90-6fa69a9af2c8.jpeg)



