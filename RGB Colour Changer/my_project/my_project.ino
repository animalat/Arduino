// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4
#define GREENPIN 10
#define BLUEPIN 9
#define REDPIN 11
int counter = 0;
int colourCounter = counter;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;
int test = 0;
int stage = 0;
int hi = 0;

void setup() {

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Serial.begin(9600);

  lastStateCLK = digitalRead(CLK);
}

void setcolour1(int red, int green, int blue)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);
}

void loop() {

  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {

    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir = " Counter Clockwise ";
    } else {
      counter ++;
      currentDir = " Clockwise ";
    }

    Serial.print("Direction:");
    Serial.print(currentDir);
    Serial.print("// Counter:");
    Serial.println(counter);
    Serial.println(colourCounter);
  }

  lastStateCLK = currentStateCLK;

  int btnState = digitalRead(SW);

  if (btnState == LOW) {

    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }

    lastButtonPress = millis();
  }

  delay(1);

  int redColour = 0;
  int blueColour = 0;
  int greenColour = 0;
  int stageSet = (stage * 357);
  int stageTell = stageSet - (51 * test);
  int test2 = 0;
  delay(1);
  if (counter >= 0) {
    colourCounter = counter;
  }
  else {
    colourCounter = counter * -1;
  }

  if (colourCounter - stageTell <= 51) {
    redColour = (colourCounter - stageTell) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 102 && colourCounter - stageTell > 51) {
    greenColour = ((colourCounter - 51) - stageTell) * 5;
    redColour = 255;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 153 && colourCounter - stageTell > 102) {
    greenColour = 255;
    redColour = 255 - ((colourCounter - 102) - stageTell) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 204 && colourCounter - stageTell > 153) {
    greenColour = 255;
    blueColour = ((colourCounter - stageTell) - 153) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 255 && colourCounter - stageTell > 204) {
    blueColour = 255;
    greenColour = 255 - ((colourCounter - 204) - stageTell) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 306 && colourCounter - stageTell > 255) {
    blueColour = 255;
    redColour = ((colourCounter - 255) - stageTell) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageTell <= 357 && colourCounter - stageTell > 306) {
    redColour = 255;
    blueColour = 255 - ((colourCounter - 306) - stageTell) * 5;
    setcolour1(redColour, blueColour, greenColour);
  }
  if (colourCounter - stageSet < 0) {
    stage--;
    test = 1;
  }
  if  (colourCounter - stageSet > 357) {
    stage++;
    test = 1;
  }
  if (colourCounter < 357) {
    test = 1;
  }
  if (btnState == LOW) {
    hi = 1;
    counter = 52;
    colourCounter = 52;
  }
}
