const int col[8]={
  13,12,11,10,9,8,7,6
};
const int row[8]={
  5,4,3,2,A4,A3,A0,A1
};

int j=0;

int button=A2;

void setup() {
  pinMode(A2,INPUT_PULLUP);
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < 8; thisPin++) { //From "Control an 8x8 Matrix of LEDS"
    // initialize the output pins:
    pinMode(row[thisPin], OUTPUT);
    pinMode(col[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(row[thisPin], HIGH);
  }
  Serial.begin(9600);
}

void loop() {

  //Serial.println(j);

  // put your main code here, to run repeatedly:
  for(int i=0; i<7;i++) {
    //Serial.println(digitalRead(A2));'
    //Serial.println(j);

    digitalWrite(row[j],LOW);
    digitalWrite(col[i],HIGH);
    delay(100);
    if (digitalRead(button)==0) {
      j++;
    }
    digitalWrite(col[i],LOW);
//    digitalWrite(row[0],LOW);
  }
  for(int i=7; i>0; i--) {
    //Serial.println(digitalRead(A2));
    //Serial.println(j);

    digitalWrite(row[j],LOW);
    digitalWrite(col[i],HIGH);
    delay(100);
    if (digitalRead(button)==0) {
      j++;
    }
    digitalWrite(col[i],LOW);
  }
}
