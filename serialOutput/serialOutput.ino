int count = 0;
void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  count++;
  Serial.print("hello jagjit!");
  Serial.println(count);
  delay(1000);

}
