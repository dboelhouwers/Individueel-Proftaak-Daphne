#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

const int buttonPin = 2;
const int standardrotation = 3;
const int greenLed = 11;
const int yellowLed = 12;
const int redLed = 13;

int loadingscreen = 0;
int buttonState = 0;
int buttonPushCounter = 0;
int lastButtonState = 0;
int count =0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  Serial.begin(9600);  
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 },
  hearth1_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000 },
  hearth2_bmp[] =
  { B00000000,
    B00000000,
    B00011000,
    B00111100,
    B00111100,
    B00011000,
    B00000000,
    B00000000 },
  hearth3_bmp[] =
  { B00000000,
    B01100110,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000,
    B00000000 },
  hearth4_bmp[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };

void loop() {

  if (loadingscreen == 0){
    //ledjes uit
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    
    //draw heart1
    matrix.setRotation(standardrotation);
    matrix.clear();
    matrix.drawBitmap(0, 0, hearth1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    //draw heart2
    matrix.clear();
    matrix.drawBitmap(0, 0, hearth2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    //draw heart3
    matrix.clear();
    matrix.drawBitmap(0, 0, hearth3_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    //draw heart4
    matrix.clear();
    matrix.drawBitmap(0, 0, hearth4_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    //draw Welkom
    matrix.setTextSize(1);
    matrix.setTextWrap(false);
    matrix.setTextColor(LED_ON);
    for (int8_t x=10; x>=-40; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("Welkom");
      matrix.writeDisplay();
      delay(100);
    }
    loadingscreen = 1;
  }
  
  else if (loadingscreen == 1){
    //read buttonpushes
    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState){
      if(buttonState == HIGH){
        buttonPushCounter++;
        Serial.println("on");
        Serial.print("number of button pushes");
        Serial.println(buttonPushCounter);
        }
      }
      else if (buttonState == LOW){
        Serial.println("off");
      }
      delay(50);
    }
    lastButtonState = buttonState;

  if (buttonPushCounter %3 == 0 && count != 3){
    matrix.setRotation(standardrotation);
    if(buttonState == HIGH){
      //set frown face
      matrix.clear();
      matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      delay(2000);
      
      //set glitchscreen
      matrix.clear();
      for(int p=0; p<15; p++){
       for(int i=0; i<8; i++){
        for (int y=0; y<8; y++){
         if(random(0,2)==0){
           matrix.drawPixel(y,i,LED_ON);
         }
        }
       }
       matrix.writeDisplay();
       delay(200);
       matrix.clear();
      }
      
      //set tekst ERROR
      matrix.setTextSize(1);
      matrix.setTextWrap(false);
      matrix.setTextColor(LED_ON);
      for (int i=0; i<4; i++){
        matrix.setRotation(i);
        for (int8_t x=7; x>=-36; x--) {
          matrix.clear();
          matrix.setCursor(x,0);
          matrix.print("ERROR");
          matrix.writeDisplay();
          delay(100);
        }
      }
      count =3;
    }
    else if (buttonState == LOW && count != 3){
      //set smile face
      matrix.clear();
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, HIGH);
      delay(500);
      matrix.clear();
    }
  }

  if (buttonPushCounter %2 == 0 && count != 3){
    
    matrix.setRotation(standardrotation);
    if(buttonState == HIGH){
      //set frown face
      matrix.clear();
      matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      delay(2000);
      
      //set tekst STOP
      matrix.setTextSize(1);
      matrix.setTextWrap(false);
      matrix.setTextColor(LED_ON);
      for (int i=0; i<4; i++){
        matrix.setRotation(i);
        for (int8_t x=7; x>=-36; x--) {
          matrix.clear();
          matrix.setCursor(x,0);
          matrix.print("STOP");
          matrix.writeDisplay();
          delay(100);
        }
      }
      //set frown face
      matrix.clear();
      matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(6000);
      digitalWrite(redLed, LOW);
      
      //set neutral face
      matrix.clear();
      matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(yellowLed, HIGH);
      delay(3000);
      digitalWrite(yellowLed, LOW);
    }
    else if (buttonState == LOW && count != 3){
      //set smile face
      matrix.clear();
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, HIGH);
      delay(500);
    }
  }
  
  if (buttonPushCounter %1 == 0 && buttonPushCounter %2 != 0 && count !=3){
    
    matrix.setRotation(standardrotation);
    if(buttonState == HIGH){
      //set neutral face
      matrix.clear();
      matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, HIGH);
      delay(2000);
      
      //set tekst 1,5 meter afstand!!
      matrix.setTextSize(1);
      matrix.setTextWrap(false);
      matrix.setTextColor(LED_ON);
      for (int8_t x=10; x>=-120; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("1,5 Meter Afstand!!!");
        matrix.writeDisplay();
        delay(100);
      }
      //set neutral face
      matrix.clear();
      matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(3000);
      digitalWrite(yellowLed, LOW);
    }
    else if (buttonState == LOW && count != 3){
      //set smile face
      matrix.clear();
      matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      digitalWrite(greenLed, HIGH);
      delay(500);
    }
  }
  if (count == 3){
     //clear matrix so you cant ped the Tamagochi because you are not allowed to these days
     matrix.clear();
     digitalWrite(redLed, LOW);
  }
}
