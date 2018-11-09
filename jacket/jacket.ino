


#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
const int buzzer = 10; 
//const int buzzerr = 9; 
int active[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int toneMap;
int micValue;
int micPin = A3;


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(buzzer,OUTPUT);
  //pinMode(buzzerr,OUTPUT);
  pinMode(micPin, INPUT);
  
  Serial.begin(9600);
  
    while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
}

//https://pages.mtu.edu/~suits/notefreqs.html
//middle c is 261.63 hz

void loop() {
  
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" touched");
      active[i] = 1;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");
      active[i] = 0;
    }
  }

  for(int i = 0; i < 12;i++){
    if(active[i]){
      toneMap = map(i, 0, 11, 185, 349);
      //Serial.println(toneMap);
      //tone(buzzer, toneMap);
      if(active[0]){
        tone(buzzer, 200);
        Serial.println("low");
      }
      if(active[2]){
        tone(buzzer, 300);
        Serial.println("mid");
      }
      if(active[1]){
        Serial.println("high");
        tone(buzzer, 400);
      }
      //tone(buzzerr, toneMap);
    }else{
      noTone(buzzer);
      //noTone(buzzerr);
      
    }
  }

  micValue = analogRead(micPin);
  //Serial.println(micValue);

  for(int i =0; i<NUMPIXELS;i++){
    //pixels.setPixelColor(i,pixels.Color(0,0,0));
    //Serial.println("something");
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  }

    if(micValue>100){
    pixels.setPixelColor(0,pixels.Color(100,0,100));
  }
  if(micValue>200){
    pixels.setPixelColor(1,pixels.Color(100,0,100));
  }
  if(micValue>300){
    pixels.setPixelColor(2,pixels.Color(100,0,100));
  }
    if(micValue>400){
    pixels.setPixelColor(3,pixels.Color(100,0,100));
  }
    if(micValue>500){
    pixels.setPixelColor(4,pixels.Color(100,0,100));
  }
      if(micValue>600){
    pixels.setPixelColor(5,pixels.Color(100,0,100));
  }
      if(micValue>700){
    pixels.setPixelColor(6,pixels.Color(100,0,100));
  }
      if(micValue>800){
    pixels.setPixelColor(7,pixels.Color(100,0,100));
  }
        if(micValue>900){
    pixels.setPixelColor(8,pixels.Color(100,0,100));
  }
        if(micValue>950){
    pixels.setPixelColor(9,pixels.Color(100,0,100));
  }
  pixels.show();

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);

}
