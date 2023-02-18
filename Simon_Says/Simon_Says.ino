// This is the code that will work if you are not using pull down
// resistors on the buttons but using INPUT_PULLUP instead.
// Define all the LED and Button pins.
// {RED, GREEN, YELLOW, BLUE}
const int buttons[] = {6, 7, 8, 9}; //The four button input pins
const int difficulty[] = {250, 1000, 500, 2000}; // Red = 250ms, Yellow = 500ms, Green = 1000ms, Blue = 2000ms,
int difficultyChosen;
const int leds[] = {2, 3, 4, 5}; // LED pins
const int BUZZER = 10;
int sequence[100];
int largestIndex = 0;
int previousGameLargestIndex = 0;
int buttonPin = 2;
const int START = 0;
const int PLAY = 1;
const int GAMEOVER = 2;
int gameState;
int speed = 500;
boolean running = true; // Flag to know is game is running
long currentMillis = 0;
long previousMillis = 0;
boolean madeMistake = false;
// the setup routine runs once when you press reset:
void setup() {
  for (int pin = 0; pin < 4; pin++)
  {
    pinMode(leds[pin], OUTPUT);
  }
  for (int pin = 0; pin < 4; pin++)
  {
    pinMode(buttons[pin], INPUT_PULLUP);
  }
  //Serial.begin(9600);
  gameState = START; // Start the game with the start.
  // initializes the pseudo-random number generator.
  randomSeed(analogRead(40));
  playSong();
}
// the loop routine runs over and over again forever:
void loop() {
  if (gameState == START)
  {
    waitToStart();
  }
  else if (gameState == PLAY)
  {
    //Serial.println("Start");
    showSequence();
    readSequence();
    if (madeMistake == false) {
      delay(500);
      blinkAll(2);
    }
    delay(500);
  }
  else if (gameState == GAMEOVER)
  {
    //Serial.println("Gameover");
    blinkAll(largestIndex - 1);
    gameState = START;
  }
}
void showSequence()
{
  //blinkRed(2);
  if ((previousGameLargestIndex <= largestIndex) && (difficultyChosen != 0))
  {
    sequence[largestIndex] = random(0, 4); //set new sequence
  }
  //Serial.println("Next out");
  //Serial.println(sequence[largestIndex]);
  largestIndex++;
  for (int index = 0; index < largestIndex; index++)
  {
    delay(300);
    digitalWrite(leds[sequence[index]], HIGH);
    playSounds(sequence[index]);
    delay(700);
    digitalWrite(leds[sequence[index]], LOW);
    noTone(BUZZER);
  }
  //blinkGreen(2);
}

void playSounds(int IndexOfLED) {
  if (IndexOfLED == 0) {
    tone(BUZZER, 261.63);
  } else if (IndexOfLED == 1) {
    tone(BUZZER, 440);
  } else if (IndexOfLED == 2) {
    tone(BUZZER, 783.99);
  } else if (IndexOfLED == 3) {
    tone(BUZZER, 1396.91);
  }
}

void readSequence()
{
  //blinkYellow(2);
  int positionPressed;
  madeMistake = false;
  for (int index = 0; index < largestIndex & madeMistake == false; index++)
  {
    //Serial.println("");
    //Serial.println("Should push");
    //Serial.println(sequence[index]);
    positionPressed = waitForButton(difficultyChosen); // 0, 1, 2, or 3
    //Serial.println("Pressed");
    //Serial.println(positionPressed);
    if (positionPressed == -1 | positionPressed != sequence[index])
    {
      madeMistake = true; // Exit the loop.
      gameState = GAMEOVER;
    }
  }
  //blinkBlue(2);
}
// Returns the position of Button pressed (0, 1, 2, or 3)
// or -1 if no button is pressed in the time period.
int waitForButton(int delayTime)
{
  int buttonPressed = -1;
  int input = HIGH;
  boolean buttonBackUp = false;
  // The number of ms since the program started running
  currentMillis = millis();
  // Records the point when we start spinning the loop.
  previousMillis = currentMillis;
  // Keep spinning the loop until "delay" seconds have passed.
  while (currentMillis - previousMillis < delayTime & buttonBackUp == false)
  {
    // Read the button and record when it has been pushed down.
    for (int pin = 0; pin < 4 & buttonBackUp == false; pin++)
    {
      if (digitalRead(buttons[pin]) == LOW)
      {
        buttonPressed = pin;
        playSounds(buttonPressed);
        //        //Serial.println(buttonPressed);
        // Show the LED pushed.
        digitalWrite(leds[pin], HIGH);
        // It is possible the button is still being pushed.
        // This loop spins until the button is let up.
        while (currentMillis - previousMillis < delayTime & buttonBackUp ==
               false)
        {
          input = digitalRead(buttons[pin]);
          if (input == HIGH)
          {
            buttonBackUp = true;
          }
          currentMillis = millis();
        }
        // See if they took too long.
        if (currentMillis - previousMillis > delayTime)
        {
          // They took to long to let the button up so they lose.
          buttonPressed = -1;
        }
        // delay to show the light pressed and
        // to handle the debounce of the button.
        delay(200);
        // Turn the LED pushed off.
        digitalWrite(leds[pin], LOW);
      }
    }
    currentMillis = millis();
  }
  noTone(BUZZER);
  return buttonPressed;
}
void waitToStart()
{
  int buttonPressed = -1;
  allOff();
  for (int pin = 0; pin < 4; pin++)
  {
    if (buttonPressed == -1)
    {
      digitalWrite(leds[pin], HIGH);
      buttonPressed = waitForButton(800);
      digitalWrite(leds[pin], LOW);
    }
  }
  if (buttonPressed != -1)
  {
    //{RED, GREEN, YELLOW, BLUE}
    difficultyChosen = difficulty[buttonPressed];
    // A button was pushed so wait then start playing.
    delay(2000);
    previousGameLargestIndex = largestIndex;
    largestIndex = 0; // Restart
    gameState = PLAY;
  }
}
// Turns all the LEDs off.
void allOff()
{
  for (int pin = 0; pin < 4; pin++)
  {
    digitalWrite(leds[pin], LOW);
  }
}
// Turns all the LEDs on.
void allOn()
{
  for (int pin = 0; pin < 4; pin++)
  {
    digitalWrite(leds[pin], HIGH);
  }
}
// Spins a loop until "delay" milliseconds passes.
// While the loop is spinning we keep looking at the
// value of the button to see if pushed.
boolean readAnyButton(int delay)
{
  boolean buttonDown = false;
  // The number of ms since the program started running
  currentMillis = millis();
  // Records the point when we start spinning the loop.
  previousMillis = currentMillis;
  // Keep spinning the loop until "delay" seconds have passed.
  while (currentMillis - previousMillis < delay & buttonDown == false)
  {
    // Read the button and record when it has been pushed down.
    for (int pin = 0; pin < 4; pin++)
    {
      if (digitalRead(buttons[pin]) == LOW)
      {
        buttonDown = true;
      }
    }
    currentMillis = millis();
  }
  return buttonDown;
}
void blinkAll(int times)
{
  for (int count = 0; count < times; count++)
  {
    allOn();
    delay(300);
    allOff();
    delay(300);
  }
}
void blinkRed(int times)
{
  for (int count = 0; count < times; count++)
  {
    digitalWrite(leds[0], HIGH);
    delay(300);
    digitalWrite(leds[0], LOW);
    delay(300);
  }
}
void blinkGreen(int times)
{
  for (int count = 0; count < times; count++)
  {
    digitalWrite(leds[1], HIGH);
    delay(300);
    digitalWrite(leds[1], LOW);
    delay(300);
  }
}
void blinkYellow(int times)
{
  for (int count = 0; count < times; count++)
  {
    digitalWrite(leds[2], HIGH);
    delay(300);
    digitalWrite(leds[2], LOW);
    delay(300);
  }
}
void blinkBlue(int times)
{
  for (int count = 0; count < times; count++)
  {
    digitalWrite(leds[3], HIGH);
    delay(300);
    digitalWrite(leds[3], LOW);
    delay(300);
  }
}

void playSong(){
tone(BUZZER, 1318.51); //E6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 987.77); //B5
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 1174.66); //D6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 987.77); //B5
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 880.00); //A5
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 880.00); //A5
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(100);

tone(BUZZER, 1318.51); //E6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1174.66); //D6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 987.77); //B5
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1174.66); //D6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1318.51); //E6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 1046.50); //C6
delay(200);
noTone(BUZZER);
delay(200);

tone(BUZZER, 880.00); //A5
delay(200);
noTone(BUZZER);
delay(200);
tone(BUZZER, 880.00); //A5
delay(200);
noTone(BUZZER);
delay(200);
}
