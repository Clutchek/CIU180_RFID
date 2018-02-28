#include <SoftwareSerial.h>
 

// Compatible ports 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
 

SoftwareSerial card1(12, 13);
SoftwareSerial card3(50, 51);
//SoftwareSerial Serial3(14,15);
//SoftwareSerial Serial2(8,9);
//SoftwareSerial comp(10,11);

//LEDS
int card2LED = 7;
int card3LED = 53;

//RGB -  Card 1
int rgbRed = 9;
int rgbGreen = 11;
int rgbBlue = 10;

 
String part1, part2, part3;
int chosenSol;
 
boolean receivedTag;

String chosenTag;
 
String tagString;
char tagNumber[14];

unsigned char buffer[64];       // buffer array for data receive over serial port
int count = 0;                    // counter for buffer array
 

String solutions[4][3];
 
void setup() {
  // put your setup code here, to run once:

  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbRed, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
  digitalWrite(rgbRed, 0);
  digitalWrite(rgbGreen, 0);
  digitalWrite(rgbBlue, 0);

  pinMode(card2LED, OUTPUT);
  pinMode(card3LED, OUTPUT);

  
  
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Serial2.begin(9600);
  Serial1.begin(9600);
  
  card1.begin(9600);
  Serial3.begin(9600);
  card3.begin(9600);
  
  
 
  //Serial.print(sol);

  //initiating chosen solution to 1 as default
  chosenSol = 1;

  //Solutions
  solutions[1][1] = "410043C377B6";
  solutions[1][2] = "410043C377B6";
  solutions[1][3] = "410043C377B6";
  //Tag Number: 410043C377B6


  
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  //delay(500);

  /*if(Serial.available()  > 0){
    char newSol = Serial.read();  
    if(newSol != chosenSol){
        
    }
  }*/

  //enabling new solution from computer
  /*if(Serial.available() > 0){
    char newSol = Serial.read();
    if(chosenSol > 0 && chosenSol < 5){
      chosenSol = newSol;  
    }
  }*/

  //Read and store what tag you want to program
  /*if(Serial2.available() > 0){
    while(Serial2.available()){
      chosenTag = Serial2.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    
  }else{
    //turn off all lamps
    
    digitalWrite(rgbRed, 0);
    digitalWrite(rgbGreen, 0);
    digitalWrite(rgbBlue, 0);
    
    digitalWrite(card2LED, LOW);
    digitalWrite(card3LED, LOW);
  }*/

  card1.listen();
  if(card1.available() > 0){
    while (card1.available()){
      int ReadBytes = card1.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
      part1 = tagNumber;
    }
    Serial.println("Tag is: " + part1);
    if(part1.equals(solutions[chosenSol][1])){
      //start pink lamp
      digitalWrite(rgbRed, 170);
      digitalWrite(rgbGreen, 0);
      digitalWrite(rgbBlue, 255);
      
    }else{
      //turn off
      digitalWrite(rgbRed, 0);
      digitalWrite(rgbGreen, 0);
      digitalWrite(rgbBlue, 0);
      
    }
  }/*else{
    //turn off lamp
    
      //digitalWrite(rgbRed, 0);
      //digitalWrite(rgbGreen, 0);
      //digitalWrite(rgbBlue, 0);
  }*/
  
  if(Serial3.available() > 0){
    while (Serial3.available()){
      int ReadBytes = Serial3.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }
    
    part2 = tagNumber;
    Serial.println("Tag is: " + part2);
    
    
    if(part2.equals(solutions[chosenSol][2])){
      //start blue led
      digitalWrite(card2LED, HIGH);
      Serial.print(" was not equal");
    }else{
      //turn off
      digitalWrite(card2LED, LOW);
    }
  }else{
    //turn off lamp
    //digitalWrite(card3LED, LOW);
  }
  
  //card3.listen();
  if(card3.available() > 0){
    Serial.println("Card 3 was avaiable");
    while (card3.available()){
      int BytesRead = card3.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    }

    part3 = tagNumber;
    Serial.println("Tag is: " + part3);
    //clearBufferArray();    

    if(part3.equals(solutions[chosenSol][3])){
      //start green lamp
      digitalWrite(card3LED, HIGH);
      //Serial.print("was equal");
    }else{
      //turn off
      digitalWrite(card3LED, LOW);
      //Serial.print("was not equal");
    }
  }else{
    //turn off lamp
    //digitalWrite(card2LED, LOW);
  }
  
  if(Serial1.available() > 0){
    tagString = "";
    while (Serial1.available()){
      int ReadBytes = Serial1.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
      tagString = tagNumber;
    }

    if(tagString.equals(chosenTag)){
      if(part1.equals(solutions[chosenSol][1]) && part2.equals(solutions[chosenSol][2]) && part3.equals(solutions[chosenSol][3])){
        //print victory over serial
        Serial.print(5);
      }else{
        //print fail over serial
        Serial.print(6);
      }
    }
  }
}

void clearBufferArray()                 // function to clear buffer array
{
    // clear all index of array with command NULL
    for (int i=0; i<count; i++)
    {
        buffer[i]=NULL;
    }                  
    count = 0;
}

