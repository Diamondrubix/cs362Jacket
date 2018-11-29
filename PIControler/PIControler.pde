import processing.serial.*;

Client client;
Serial myPort;
String ip = "localhost";
int port = 3001;
void setup(){
  //surface.setVisible(false);
size(900, 600);
background(255,255,255);
stroke(255,255,255);
fill(0,100,255);

  println("starting pi controler");
  
  try {
      client = new Client(ip, port);
  //myPort = new Serial(this, Serial.list()[0], 9600);
  //myPort.bufferUntil('\n');
} catch (IOException e) {
}


      
}

void draw(){
  rect(0,0,100,100);
}

void keyPressed(){
  if(key == 'a'){
    println("pi 2");
    client.sendData("PI:2");
  }
  if(key =='s'){
    println("pi 0");
    client.sendData("PI:0");
  }
  if(key == 'd'){
    println("pi 1");
    client.sendData("PI:1");
  }
  
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    if(inString.equals("toggle")){
      client.sendData("PI:0");
    }else if(inString.equals("next")){
      client.sendData("PI:1");
    }else if(inString.equals("previous")){
      client.sendData("PI:2");
    }else{
      println("this should not run");
    }
  }
}
