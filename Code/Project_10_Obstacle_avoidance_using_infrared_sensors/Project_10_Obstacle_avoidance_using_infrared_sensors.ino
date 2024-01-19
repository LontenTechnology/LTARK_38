// set pin numbers
const int valuePin = 4;  

int value;
void setup() {
  Serial.begin(115200);  
  // initialize the pin as an input
  pinMode(valuePin, INPUT);
}

void loop() {
  value = digitalRead(valuePin);
  Serial.println(value);
  delay(100);
}


