#include "LedControl.h"
#include "DS3231.h"

#define EXHIBIT 0
#define TEST 1
#define DEMO 2

int MODE = EXHIBIT;
LedControl lc1 = LedControl(2, 3, 4, 1);
LedControl lc2 = LedControl(5, 6, 7, 1);  
DS3231 rtc(SDA, SCL);


int IT[11]            = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int IS[11]            = {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0};
int AM[11]            = {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};
int PM[11]            = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
int A[11]             = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int QUARTER[11]       = {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0};
int TWENTY[11]        = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
int FIVE_M[11]        = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0};
int TWENTY_FIVE[11]   = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
int HALF[11]          = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
int TEN_M[11]         = {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};
int TO[11]            = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
int PAST[11]          = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
int NINE[11]          = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int ONE[11]           = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int SIX[11]           = {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
int THREE[11]         = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
int FOUR[11]          = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
int FIVE_H[11]        = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0};
int TWO[11]           = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
int EIGHT[11]         = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int ELEVEN[11]        = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
int SEVEN[11]         = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
int TWELVE[11]        = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
int TEN_H[11]         = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int OCLOCK[11]        = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};

int mainMatrix[10][11] = 
  {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

unsigned long delaytime=25;
int leds=8;
int intensity = 15;

void setup() {

  lc1.shutdown(0,false);
  lc1.setIntensity(0,intensity);
  lc1.clearDisplay(0);
  
  lc2.shutdown(0, false);
  lc2.setIntensity(0, intensity);
  lc2.clearDisplay(0);

  rtc.begin();

  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setDate(4, 8, 2017);   // Set the date to January 1st, 2014
  //rtc.setTime(8, 51, 10);     // Set the time to 12:00:00 (24hr format)
  Serial.begin(9600);
}

void loop() 
{ 

  switch(MODE) 
  {
    case EXHIBIT:
      doExhibit();
      break;
    case TEST:
      doLEDTest();
      break;  
    case DEMO:
      doDemo();
      break;
  }
  
}

void doExhibit() 
{
  String t = rtc.getTimeStr();

  Serial.println(t);
  char hh[3];
  char mm[3];

  hh[0] = t.charAt(0);
  hh[1] = t.charAt(1); 
  hh[2] = '\0';

  mm[0] = t.charAt(3);
  mm[1] = t.charAt(4);
  mm[2] = '\0';

  int hours = atoi(hh);
  int minutes = atoi(mm);
  resetMatrix();
  displayTime(hours, minutes);
  //printMatrix();
  applyMatrix();
  delay(15000);
}

void displayTime(int hours, int minutes)
{
  applyMask(0, IT);
  applyMask(0, IS);

  boolean isA    = (minutes >= 13 && minutes <= 17) || (minutes >= 43 && minutes <= 47); // quarter
  boolean isPast = minutes >=  3 && minutes <= 32;
  boolean isTo = minutes >= 33 && minutes <= 57;

  if (isA) { applyMask(1, A); }

  // isPast = true:  PAST is active
  // isPast = false: TO   is active
  if(isPast) { applyMask(4, PAST); }
  if(isTo) { applyMask(3, TO); hours = ((hours%12) + 1); }

  if (minutes >= 58) {  applyMask(9, OCLOCK); /* o'clock */ hours = ((hours%12) + 1); }
  
  if     (hours%12 == 0)  { applyMask(8, TWELVE); }
  else if (hours%12 == 1)  { applyMask(5, ONE); }
  else if (hours%12 == 2)  { applyMask(6, TWO); }
  else if (hours%12 == 3)  { applyMask(5, THREE); }
  else if (hours%12 == 4)  { applyMask(6, FOUR); }
  else if (hours%12 == 5)  { applyMask(6, FIVE_H); }
  else if (hours%12 == 6)  { applyMask(5, SIX); }
  else if (hours%12 == 7)  { applyMask(8, SEVEN); }
  else if (hours%12 == 8)  { applyMask(7, EIGHT); }
  else if (hours%12 == 9)  { applyMask(4, NINE); }
  else if (hours%12 == 10) { applyMask(9, TEN_H); }
  else if (hours%12 == 11) { applyMask(7, ELEVEN); }

  if      (minutes >= 58 || minutes <= 2)       {  applyMask(9, OCLOCK); /* o'clock */ }
  else if (minutes >= 3 && minutes <= 7)   {  applyMask(2, FIVE_M); /* five past */ }
  else if (minutes >= 8 && minutes <= 12)  {  applyMask(3, TEN_M); /* ten past */ }
  else if (minutes >= 13 && minutes <= 17) {  applyMask(1, QUARTER); /* quarter past */ }
  else if (minutes >= 18 && minutes <= 22) {  applyMask(2, TWENTY); /* twenty past */ }
  else if (minutes >= 23 && minutes <= 27) {  applyMask(2, TWENTY_FIVE); /* twenty five past */ }
  else if (minutes >= 28 && minutes <= 32) {  applyMask(3, HALF); /* half past */ }
  else if (minutes >= 33 && minutes <= 37) {  applyMask(2, TWENTY_FIVE); /* twenty five to*/ }
  else if (minutes >= 38 && minutes <= 42) {  applyMask(2, TWENTY); /* twenty to */ }
  else if (minutes >= 43 && minutes <= 47) {  applyMask(1, QUARTER); /* quarter to */ }
  else if (minutes >= 48 && minutes <= 52) {  applyMask(3, TEN_M); /* ten to */ }
  else if (minutes >= 53 && minutes <= 57) {  applyMask(2, FIVE_M); /* five to */ }
  
}

void resetMatrix()
{
  for(int row = 0; row < 10; row++)
  {
    for(int col = 0; col < 11; col++) 
    {
      mainMatrix[row][col] = mainMatrix[row][col] && 0;  
    }
  }
}

void applyMask(int row, int mask[]) 
{
  for(int i = 0; i < 11; i++)
  {
    mainMatrix[row][i] = mainMatrix[row][i] || mask[i];   
  }
}

void applyMatrix()
{
  for(int row = 0; row < 10; row++)
  {
    for(int col = 0; col < 11; col++) 
    {
      setLed(row, col, mainMatrix[row][col] == 1);
      if (mainMatrix[row][col] == 1) 
      { 
        delay(10); 
      }
    }
  }
}

void printMatrix()
{
  for(int row = 0; row < 10; row++)
  {
    for(int col = 0; col < 11; col++)
    {
      Serial.print(mainMatrix[row][col]);
      Serial.print(" ");  
    }  
    Serial.println();
  }  
  Serial.println("----------------------");
}

void doDemo()
{
  for(int h = 0; h < 24; h++)
  {
    for(int m = 0; m < 60; m++)
    {
      int hours = h;
      int minutes = m;
      resetMatrix();
      displayTime(hours, minutes);
      printMatrix();
      applyMatrix();
      delay(500);    
    }
  }
}

void doLEDTest()
{
  for(int row = 0; row < 10; row++)
  {
    for(int col = 0; col < 11; col++)
    {
      setLed(row, col, true);
      delay(delaytime);
      setLed(row, col, false);
      delay(delaytime);
    }
  }

  for(int y = 0; y < 11; y++)
  {
    for(int x = 0; x < 10; x++)
    {
      setLed(x, y, true);
      delay(delaytime);
      setLed(x, y, false);
      delay(delaytime);
    }
  }  
}

void setLed(int x, int y, boolean isOn)
{
  if(x < 8)
  {
    if(y < 8)
    {
      lc1.setLed(0, x, y, isOn);  
    }
    else
    {
      if( y == 8 || y == 9 || y == 10)
      {
        if(y == 8)  { lc2.setLed(0, x, 3, isOn); }
        if(y == 9)  { lc2.setLed(0, x, 4, isOn); }
        if(y == 10) { lc2.setLed(0, x, 5, isOn); }
      }
    }
  }
  else
  {
    // x >= 8
    if(y == 0) {  lc2.setLed(0, x == 8 ? 6 : 7, 0, isOn); }
    if(y == 1) {  lc2.setLed(0, x == 8 ? 6 : 7, 1, isOn); }
    if(y == 2) {  lc2.setLed(0, x == 8 ? 6 : 7, 2, isOn); }
    if(y == 3) {  lc2.setLed(0, x == 8 ? 6 : 7, 7, isOn); }
    if(y == 4) {  lc2.setLed(0, x == 8 ? 4 : 5, 0, isOn); }
    if(y == 5) {  lc2.setLed(0, x == 8 ? 4 : 5, 1, isOn); }
    if(y == 6) {  lc2.setLed(0, x == 8 ? 4 : 5, 2, isOn); }
    if(y == 7) {  lc2.setLed(0, x == 8 ? 4 : 5, 7, isOn); }
    if(y == 8) {  lc2.setLed(0, x == 8 ? 2 : 3, 0, isOn); }
    if(y == 9) {  lc2.setLed(0, x == 8 ? 2 : 3, 1, isOn); }
    if(y == 10) { lc2.setLed(0, x == 8 ? 2 : 3, 2, isOn); }
    }  
}
