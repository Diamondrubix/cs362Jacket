import processing.serial.*;

CLient client;
Serial myPort;
  
void setup(){
  surface.setVisible(false);
  println("starting pi controler");
  client = new Client("localhost", 3001);
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
      
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    if(inString.equals("toggle"){
      client.send("PI:0");
    }else if(inString.equals("next"){
      client.send("PI:1");
    }else if(inString.equals("previous"){
      client.send("PI:2");
    }else{
      println("this should not run");
    }
  }
}
