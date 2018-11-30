
const int trigPin = 2;
const int echoPin = 3;


#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

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

long duration, inches, cm;
void setup() {
      // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
}

void loop() {
    
    for(int i =0; i<NUMPIXELS;i++){
    //pixels.setPixelColor(i,pixels.Color(0,0,0));
    //Serial.println("something");
    pixels.setPixelColor(i,pixels.Color(0,0,0));
  }

  
  if(inches>3){
    pixels.setPixelColor(0,pixels.Color(100,0,100));
  }
  if(inches>6){
    pixels.setPixelColor(1,pixels.Color(100,0,100));
  }
  if(inches>9){
    pixels.setPixelColor(2,pixels.Color(100,0,100));
  }
    if(inches>12){
    pixels.setPixelColor(3,pixels.Color(100,0,100));
  }
    if(inches>15){
    pixels.setPixelColor(4,pixels.Color(100,0,100));
  }
      if(inches>18){
    pixels.setPixelColor(5,pixels.Color(100,0,100));
  }
      if(inches>21){
    pixels.setPixelColor(6,pixels.Color(100,0,100));
  }
      if(inches>24){
    pixels.setPixelColor(7,pixels.Color(100,0,100));
  }
        if(inches>27){
    pixels.setPixelColor(8,pixels.Color(100,0,100));
  }
        if(inches>30){
    pixels.setPixelColor(9,pixels.Color(100,0,100));
  }
  

  
  pixels.show();
    // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:


  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  
}


long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
