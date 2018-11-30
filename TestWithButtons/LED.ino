
int prevB = 8;
int togB = 9;
int nextB = 10;
boolean prev = false;
boolean tog = false;
boolean next = false;
boolean pressed = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(prevB, INPUT);
  pinMode(togB, INPUT);
  pinMode(nextB, INPUT);
  Serial.begin(9600);
  
  
}

void loop() {

  prev = digitalRead(prevB);
  tog = digitalRead(togB);
  next = digitalRead(nextB);


  
  if(tog && pressed == false){
    Serial.println("toggle");
    pressed = true;
  }else if(prev && pressed ==false){
    Serial.println("prev");
    pressed = true;
  }else if(next && pressed ==false){
    Serial.println("next");
    pressed = true;
  }
    if(prev || tog || next){
    pressed = true;
  }else{
    pressed = false;
  }
  
  

}
