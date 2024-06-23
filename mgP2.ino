void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0,OUTPUT);
}

int buttonPressed=0;

void loop() {
  Serial.println(digitalRead(A1));
  if(digitalRead(A1)==0 && buttonPressed==0) {
    buttonPressed=1;
  }
  else if(digitalRead(A1)==0 && buttonPressed==1) {
    buttonPressed=0;
  }
  if(buttonPressed==1) {
    analogWrite(A0,255);
  }
  else {
    analogWrite(A0,0);
  }
  Serial.println("BUTTON");
  Serial.println(buttonPressed);
  delay(100);
  // put your main code here, to run repeatedly:

}
