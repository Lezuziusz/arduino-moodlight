/*
* Moodlight 1.0
* Peter Alt - peter@bitflimmern.de
*
* Color of light can be switched with the button pressed.
* White means color fading. Light switches off automatically
* after 30 Minutes.
*
*/

// Define the pins here
int red = 11;
int green = 10;
int blue = 9;
int button = 8;

// If true, light will start with fading 
// instead of black
boolean fade = false;

// Time out to turn off the lights (secs)
long sleepTime = 30;

// Preview of colors in selection mode
int delayWait = 800;

// *** *** *** *** *** //
// No need to configure anything below
// *** *** *** *** *** //

// Global Power conditions
int powerRed = 0;
int powerGreen = 0;
int powerBlue = 0;

long currentTime = 0;
long timeToSleep = 0;

// used for fading algorithm
float counter = 0;

void setup()
{
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(button, INPUT);
  randomSeed(analogRead(0));
  // convert minutes to milliseconds
  sleepTime = sleepTime * 60 * 1000;
  // activate time-out counter on setup
  // only useful if fading is activated
  timeToSleep = millis() + sleepTime;
  // set black
  setColor(0,0,0,1);
}

void loop()
{
  currentTime = millis();
  // if timed out
  if(currentTime > timeToSleep)
  {
   setColor(0,0,0, 1000);
   fade = false;
  }
  fader();
  checkButton(); 
}

void setColor(int red, int green, int blue, int speedIndex)
{
  while(powerGreen != green || powerBlue != blue || powerRed != red)
  {
     if(powerRed > red)
      powerRed -= 1;
     if(powerGreen > green)
      powerGreen -= 1;
     if(powerBlue > blue)
      powerBlue -= 1;
     if(powerRed < red)
      powerRed += 1;
    if(powerGreen < green)
      powerGreen += 1;
    if(powerBlue < blue)
      powerBlue += 1;
     writePower();
     if(speedIndex < 1000)
       delayMicroseconds(speedIndex); 
     else
       delay(speedIndex/3);
  }
}

void checkButton()
{
  //PURPLE  
  if(digitalRead(button) == 1)
  {  
       setColor(255, 0, 255, 800);
       delay(delayWait);
       fade = false;
       timeToSleep = currentTime + sleepTime;
  }    
  // RED
  if(digitalRead(button) == 1)
  {
      setColor(255, 0, 0, 800);
      delay(700);
      fade = false;
      timeToSleep = currentTime + sleepTime; 
  }
  // ORANGE
  if(digitalRead(button) == 1)
  {  
      setColor(255, 255/2, 0, 800);
      delay(delayWait);
      fade = false;
      timeToSleep = currentTime + sleepTime;
  }
  // YELLOW
  if(digitalRead(button) == 1)
  {  
      setColor(200, 200, 25, 800);
      delay(delayWait);
      fade = false;
      timeToSleep = currentTime + sleepTime;
  }       
  // GREEN
  if(digitalRead(button) == 1)
  {  
       setColor(0, 255, 0, 800);
       delay(delayWait);
       fade = false;
       timeToSleep = currentTime + sleepTime;
  }
  // BLUE
  if(digitalRead(button) == 1)
  { 
       setColor(0, 0, 255, 800);   
       delay(delayWait);
       fade = false;
       timeToSleep = currentTime + sleepTime;
  }
  // TÜRKIS 
  if(digitalRead(button) == 1)
  {  
       setColor(0, 255, 255, 800);   
       delay(delayWait);
       fade = false;
       timeToSleep = currentTime + sleepTime;
  }  
  // WHITE
  if(digitalRead(button) == 1)
  {  
      setColor(200, 200, 200, 800);  
      delay(delayWait);
      fade = true;
      timeToSleep = currentTime + sleepTime; 
  }
  // OFF
  if(digitalRead(button) == 1)
  {  
     setColor(0, 0, 0, 800); 
     delay(delayWait);
     fade = false;
  }
}

void writePower()
{
   analogWrite(blue, powerBlue);
   analogWrite(green, powerGreen);
   analogWrite(red, powerRed); 
}

void neutralizeColor()
{
  powerRed = powerGreen = powerBlue = 0; 
}

void fader()
{
 if(fade)
 {
   powerGreen = abs(sin(counter)*255);
   powerRed = abs(sin(counter+0.5)*255);
   powerBlue= abs(cos(counter)*255);
   counter+= 0.005;
   writePower();
   delay(150);
 } 
}
