#include <SoftwareSerial.h>
 

// Compatible ports 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
 


//Card1 - Serial3 (15)
//Card2 - Serial2
//Card3 - Serial1

#define card1 Serial3
#define card2 Serial2
#define card3 Serial1

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
 
String solutions[4][3];

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
  
  pinMode(readerGreen, OUTPUT);
  pinMode(readerRed, OUTPUT);
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
  chosenSol = 1;

  //The tag number of the tag that you want to "program"
  chosenTag = "410042E50AEC";

  //Solutions
  solutions[1][1] = "410043C377B6";
  solutions[1][2] = "410043C377B6";
  solutions[1][3] = "410043C377B6";
  //Tag Number: 410043C377B6

}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  //delay(500);

  //enabling new solution from computer
  /*if(Serial.available() > 0){
    char newSol = Serial.read();
    if(chosenSol > 0 && chosenSol < 5){
      chosenSol = newSol;  
    }
  }*/
  
  if(card1.available() > 0){
    while (card1.available()){
      int ReadBytes = card1.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
      part1 = tagNumber;
    }
    Serial.println("Tag is: " + part1);
    if(part1.equals(solutions[chosenSol][1])){
      //Solution found, turning on green
      digitalWrite(rgb1Red, 0);
      digitalWrite(rgb1Green, 255);
      digitalWrite(rgb1Blue, 0);
      
    }else{
      //Solution not found, turning on red
      digitalWrite(rgb1Red, 255);
      digitalWrite(rgb1Green, 0);
      digitalWrite(rgb1Blue, 0);
    }
  }
  
  if(card2.available() > 0){
    while (card2.available()){
      int ReadBytes = card2.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    part2 = tagNumber;
    Serial.println("Tag is: " + part2);
    
    
    if(part2.equals(solutions[chosenSol][2])){
      //Solution found, turning on green
      digitalWrite(rgb2Red, 0);
      digitalWrite(rgb2Green, 255);
      digitalWrite(rgb2Blue, 0);
    }else{
      //Solution not found, turning on red
      digitalWrite(rgb2Red, 255);
      digitalWrite(rgb2Green, 0);
      digitalWrite(rgb2Blue, 0);
      
    }
  }
  
  if(card3.available() > 0){
    Serial.println("Card 3 was avaiable");
    while (card3.available()){
      int BytesRead = card3.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }

    part3 = tagNumber;
    Serial.println("Tag is: " + part3);
    //clearBufferArray();    

    if(part3.equals(solutions[chosenSol][3])){
      //Solution found, turning on green
      digitalWrite(rgb3Red, 0);
      digitalWrite(rgb3Green, 255);
      digitalWrite(rgb3Blue, 0);
      
    }else{
      //Solution not found, turning on red
      digitalWrite(rgb3Red, 255);
      digitalWrite(rgb3Green, 0);
      digitalWrite(rgb3Blue, 0);
    }
  }
  
  if(reader.available() > 0){
    tagString = "";
    while (reader.available()){
      int ReadBytes = reader.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    tagString = tagNumber;
    Serial.println(tagString);

    if(tagString.equals(chosenTag)){
      if(part1.equals(solutions[chosenSol][1]) && part2.equals(solutions[chosenSol][2]) && part3.equals(solutions[chosenSol][3])){
        //print victory over serial
        Serial.print(5);
        digitalWrite(readerRed, 0);
        digitalWrite(readerGreen, 255);
        digitalWrite(readerBlue, 0);
        
      }else{
        //print fail over serial
        Serial.print(6);
        digitalWrite(readerRed, 255);
        digitalWrite(readerGreen, 0);
        digitalWrite(readerBlue, 0);
      }
    }else{
        //wrong tag scanned
        digitalWrite(readerRed, 255);
        digitalWrite(readerGreen, 0);
        digitalWrite(readerBlue, 0);
    }
  }
}

