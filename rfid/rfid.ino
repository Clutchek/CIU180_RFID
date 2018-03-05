#include <SoftwareSerial.h>
 

// Compatible ports 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
 


//Card1 - Serial3 (15)
//Card2 - Serial2
//Card3 - Serial1

//Defining the different cards that are used for each port
#define card1 Serial3
#define card2 Serial2
#define card3 Serial1

#define MAX_ROWS 4
#define MAX_COLS 3

//The rfid that confirms the solution is using the softwareserial library
SoftwareSerial reader(50, 51);

//RGB -  Card 1
int rgb1Red = 9;
int rgb1Green = 11;
int rgb1Blue = 10;

//RGB - Card 2
int rgb2Red = 6;
int rgb2Green = 5;
int rgb2Blue = 4;

//RGB - Card 3
int rgb3Red = 36;
int rgb3Green = 37;
int rgb3Blue = 39;

//RGB - Reader

int readerRed = 49;
int readerGreen = 48;
int readerBlue = 53;
 
String part1, part2, part3;
int chosenSol;
 
boolean receivedTag;

String chosenTag;
 
String tagString;
char tagNumber[14];

//unsigned char buffer[64];       // buffer array for data receive over serial port
//int count = 0;                    // counter for buffer array


int solRows = 5;
int solCols = 3;
String solutions[MAX_ROWS][MAX_COLS];

int delayTime = 1000;
 
void setup() {
  // put your setup code here, to run once:

  //start the lights and make sure they are not displaying any colors
  pinMode(rgb1Green, OUTPUT);
  pinMode(rgb1Red, OUTPUT);
  pinMode(rgb1Blue, OUTPUT);
  digitalWrite(rgb1Red, 0);
  digitalWrite(rgb1Green, 0);
  digitalWrite(rgb1Blue, 0);

  pinMode(rgb2Green, OUTPUT);
  pinMode(rgb2Red, OUTPUT);
  pinMode(rgb2Blue, OUTPUT);
  digitalWrite(rgb1Red, 0);
  digitalWrite(rgb1Green, 0);
  digitalWrite(rgb1Blue, 0);

  pinMode(rgb3Green, OUTPUT);
  pinMode(rgb3Red, OUTPUT);
  pinMode(rgb3Blue, OUTPUT);
  digitalWrite(rgb3Red, 0);
  digitalWrite(rgb3Green, 0);
  digitalWrite(rgb3Blue, 0);

  pinMode(readerRed, OUTPUT);
  pinMode(readerGreen, OUTPUT);
  pinMode(readerBlue, OUTPUT);
  digitalWrite(readerRed, 0);
  digitalWrite(readerGreen, 0);
  digitalWrite(readerBlue, 0);
  
  //Start the connection to the computer
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  //Start the rfid readers
  Serial3.begin(9600);
  Serial2.begin(9600);
  Serial1.begin(9600);
  reader.begin(9600);

  reader.listen();
  
  //initiating chosen solution to 1 as default
  chosenSol = 0;

  //The tag number of the tag that you want to "program"
  chosenTag = "410042E50AEC";

  part1= "";
  part2= "";
  part3= "";


  //Solutions to the game. The first number indicates the number of the solution and the second number is the solutions sub parts.
  solutions[0][0] = "410043C377B6";
  solutions[0][1] = "410043C377B6";
  solutions[0][2] = "410043C377B6";

  solutions[1][0] = "410043C377B6";
  solutions[1][1] = "410043C377B6";
  solutions[1][2] = "410043C377B6";

  solutions[2][0] = "410043C377B6";
  solutions[2][1] = "410043C377B6";
  solutions[2][2] = "410043C377B6";

  solutions[3][0] = "410043C377B6";
  solutions[3][1] = "410043C377B6";
  solutions[3][2] = "410043C377B6";
  
  solutions[4][0] = "410043C377B6";
  solutions[4][1] = "410043C377B6";
  solutions[4][2] = "410043C377B6";
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  //delay(500);

  //enabling new solution from computer
  if(Serial.available() > 0){
    char newSol = Serial.read();
    if(chosenSol > 0 && chosenSol < 5){
      chosenSol = newSol;
      //Serial.println(chosenSol);  
      resetLeds();
    }
  }
  
  if(card1.available() > 0){
    while (card1.available()){
      int ReadBytes = card1.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
      part1 = tagNumber;
    }
    //Serial.println("Card 1 registered tag as: " + part1);
    if(isCorrectType(1, part1)){
      //Card type was correct, turn on blue light
      setLedColor(rgb1Red, rgb1Green, rgb1Blue, "blue");
      
    }else{
      //Card type was not correct, turning on red
      setLedColor(rgb1Red, rgb1Green, rgb1Blue, "red");
    }
  }
  
  if(card2.available() > 0){
    while (card2.available()){
      int ReadBytes = card2.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    part2 = tagNumber;
    //Serial.println("Card 2 registered tag as: " + part2);
    
    
    if(isCorrectType(2, part2)){
      //Card type was correct, turn on blue light
      setLedColor(rgb2Red, rgb2Green, rgb2Blue, "blue");
    }else{
      //Card type was not correct, turn on red light
      setLedColor(rgb2Red, rgb2Green, rgb2Blue, "red");
    }
  }
  
  if(card3.available() > 0){
    while (card3.available()){
      int BytesRead = card3.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    part3 = tagNumber;
    //Serial.println("Card 3 registered tag as: " + part3);

    if(isCorrectType(3, part3)){
      //Card type was correct, turn on blue light
      setLedColor(rgb3Red, rgb3Green, rgb3Blue, "blue");
    }else{
      //Card type was not correct, turn on red light
      setLedColor(rgb3Red, rgb3Green, rgb3Blue, "red");
    }
  }
  
  if(reader.available() > 0){
    tagString = "";
    while (reader.available()){
      int ReadBytes = reader.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    tagString = tagNumber;
    //Serial.println(tagString);
    //chosenTag = "410042E50AEC";
    //Serial.println(chosenTag);
    if(chosenTag.equals(tagString)){
      
      if(part1.equals(solutions[chosenSol][0])){
        //part was correct, turn on green light
        setLedColor(rgb1Red, rgb1Green, rgb1Blue, "green");
      }else{
        //part was incorrect, turn on red light
        setLedColor(rgb1Red, rgb1Green, rgb1Blue, "red");
      }

      if(part2.equals(solutions[chosenSol][1])){
        //part was correct, turn on green light
        setLedColor(rgb2Red, rgb2Green, rgb2Blue, "green");
      }else{
        //part was incorrect, turn on red light
        setLedColor(rgb2Red, rgb2Green, rgb2Blue, "red");
      }

      //Serial.println(solutions[chosenSol][2]);
      //Serial.println(part3);
      //Serial.println(part2);
      //Serial.println(part1);
      if(part3.equals(solutions[chosenSol][2])){
        //part was correct, turn on green light
        setLedColor(rgb3Red, rgb3Green, rgb3Blue, "green");
      }else{
        //part was incorrect, turn on red light
        setLedColor(rgb3Red, rgb3Green, rgb3Blue, "red");
      }
      
      //Sending data over serial to display victory/failure states on computer screen
      if(part1.equals(solutions[chosenSol][0]) && part2.equals(solutions[chosenSol][1]) && part3.equals(solutions[chosenSol][2])){
        //print victory over serial
        setLedColor(readerRed, readerGreen, readerBlue, "green");
        Serial.print(5);
      }else{
        //print fail over serial
        setLedColor(readerRed, readerGreen, readerBlue, "red");
        Serial.print(6);
      }
    }
    //wrong tag scanned, do noting
    
  }
}

//method to save some repetition in starting lights
void setLedColor(int redPin, int greenPin, int bluePin, String color){
  if(color.equals("blue")){
    digitalWrite(redPin, 0);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 255);
  }else if(color.equals("red")){
    digitalWrite(redPin, 255);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
  }else if(color.equals("green")){
    digitalWrite(redPin, 0);
    digitalWrite(greenPin, 255);
    digitalWrite(bluePin, 0);
  }else if(color.equals("off")){
    digitalWrite(redPin, 0);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
  }
  //else do nothing
}

//method to find out if a scanned tag is of the correct type of the used reader
boolean isCorrectType(int cardNumber,String scannedTag){
  int j;
  boolean wasFound = false;
  for(j = 0; j < MAX_ROWS; j++){
    if(scannedTag.equals(solutions[j][cardNumber-1])){
      wasFound = true;
    }
  }
  return wasFound;
}

//Turning off all leds
void resetLeds(){
  digitalWrite(rgb1Red, 0);
  digitalWrite(rgb1Green, 0);
  digitalWrite(rgb1Blue, 0);

  digitalWrite(rgb1Red, 0);
  digitalWrite(rgb1Green, 0);
  digitalWrite(rgb1Blue, 0);

  digitalWrite(rgb2Red, 0);
  digitalWrite(rgb2Green, 0);
  digitalWrite(rgb2Blue, 0);

  digitalWrite(rgb3Red, 0);
  digitalWrite(rgb3Green, 0);
  digitalWrite(rgb3Blue, 0);

  digitalWrite(readerRed, 0);
  digitalWrite(readerGreen, 0);
  digitalWrite(readerBlue, 0); 
}

