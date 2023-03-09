const int col[8]={ //Column Pins
  13,12,11,10,9,8,7,6
};
const int row[8]={ //Row Pins
  5,4,3,2,A4,A3,A0,A1
};

int j=0; //Used to iterate the pixel up rows
int curCol=0; //Used to iterate the pixel down the columns
int button=A2; //Button pin
int direction=-1; //Used to change direction
int win=255; //Used to find whether a win has happened
int pixels[8]; //Matrix of pixels: Works by using bit shifting
bool buttonPressed=0; //Button press bool
long int time; //Keeps time

void setup() {
  digitalWrite(A5,HIGH); //Reset Pin
  pinMode(A5,OUTPUT);

  time = millis(); //Sets the time
  pinMode(button,INPUT_PULLUP); //Sets the button
  for (int i = 0; i < 8; i++) {  //Sets the rows and columns to output mode and turns the rows on high
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    digitalWrite(row[i], HIGH);
  }
  for (int i=0; i < 8; i++){ //Sets the pixels to 0
    pixels[i]=0;
  }
}

void loop() {
  long int elapsed=millis()-time; //Time elapsed: This allows the game to speed up and move over time
  if(elapsed>200 - 1.75 * ((j * 8) + (8 - j))){ //Speeds the matrix up as the game is played
    if(curCol==0||curCol==7) { //Switches directions
      direction*=-1;
    }
    pixels[j]&=~(1<<curCol);
    curCol+=direction;
    time=millis(); //Resets time
  }

  if((digitalRead(button)==0) && buttonPressed==0 && j<=8) { //Button is pressed
    buttonPressed=1;
    j++; //Increment up a row
    pixels[j]|=1<<curCol; 
    win&=pixels[j];
  }
  else if(digitalRead(button)==1){ //Button is not pressed
    buttonPressed=0; 
  }

  if(!win) { //Lose Conditions
    Serial.println("YOU LOSE");
    for(int i=0; i<8; i++) { //Sets up pixel art for an 'L'
      pixels[i]=0;
    }
    pixels[7]=B00000000;
    pixels[6]=B00000100;
    pixels[5]=B00000100;
    pixels[4]=B00000100;
    pixels[3]=B00000100;
    pixels[2]=B00000100;
    pixels[1]=B00111100;
    pixels[0]=B00000000;

  while(true) {
    for(int i=0; i<8; i++) {
      digitalWrite(row[i],LOW); //Turns the ROW ON
      for(int k=0; k<8;k++) {
          if ((pixels[i]>>k)&1) { //Bitshifting
            digitalWrite(col[k],HIGH); //Turns the COLUMN ON
          }
        }
        delay(1);
        for(int k=0; k<8; k++) {
          digitalWrite(col[k],LOW); //Turns the COLUMN OFF
        }
        digitalWrite(row[i],HIGH); //Turns the ROW OFF
    }
    if((digitalRead(button)==0) && buttonPressed==0) {
      buttonPressed=1;
      break;
    }
    else if(digitalRead(button)==1){
      buttonPressed=0;
    }
  }
    digitalWrite(A5,LOW); //Resets program
  }

  if(j>7 && win) { //Win Condition
    Serial.println("YOU WIN");
    for(int i=0; i<8; i++) { //Sets up pixel art for a 'W'
      pixels[i]=0;
    }
    pixels[7]=B00000000;
    pixels[6]=B01000010;
    pixels[5]=B01000010;
    pixels[4]=B01000010;
    pixels[3]=B01011010;
    pixels[2]=B01100110;
    pixels[1]=B01000010;
    pixels[0]=B00000000;

    while(true) {
      for(int i=0; i<8; i++) {
        digitalWrite(row[i],LOW); //Turns the ROW ON
        for(int k=0; k<8;k++) {
            if ((pixels[i]>>k)&1) { //Bitshifting
              digitalWrite(col[k],HIGH); //Turns the COLUMN ON
            }
          }
          delay(1);
          for(int k=0; k<8; k++) {
            digitalWrite(col[k],LOW); //Turns the COLUMN OFF
          }
          digitalWrite(row[i],HIGH); //Turns the ROW OFF
      }
      if((digitalRead(button)==0) && buttonPressed==0) {
        buttonPressed=1;
        break;
      }
      else if(digitalRead(button)==1){
        buttonPressed=0;
      }
    }
    digitalWrite(A5,LOW); //Resets the program
  }

  pixels[j]|=1<<curCol; 
  for(int i=0; i<8; i++) {
    digitalWrite(row[i],LOW); //Turns the ROW ON
    for(int k=0; k<8;k++) {
      if ((pixels[i]>>k)&1) { //Bitshifting
        digitalWrite(col[k],HIGH); //Turns the COLUMN ON
      }
    }
    delay(1); //Allows for the pixel to move across
    for(int k=0; k<8; k++) {
      digitalWrite(col[k],LOW); //Turns the COLUMN OFF
    }
    digitalWrite(row[i],HIGH); //Turns the ROW OFF
  }
  return;
}
