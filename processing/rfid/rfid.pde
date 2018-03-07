import processing.serial.*;
import processing.sound.*;

//Positions of buttons
int[] btnX;

//Y pos is same for all buttons
int btnY;

//Width and height of buttons
int btnWidth, btnHeight;

int nbrOfBtns;

//Default color and color when mouse is hovering over
color btnColor;
color highlightColor;

Serial myPort;

//Descriptions of the different exercises
String[] exerciseDescs;

int chosenExercise; //The exercise that has been chosen, may range from 0-4
int endState; //Represents if an endstate has occured. 0 is false, 5 is win, 6 is loss

//Hover state of each button
boolean[] btnHover;

SoundFile winFile, failFile;

void setup(){
  //Settings for window and graphics
  size(1280,720);
  background(255,255,255);
  pixelDensity(2);
  
  //Load sound files
  failFile = new SoundFile(this, "fail.mp3");
  winFile = new SoundFile(this, "win.wav");
  
  //Set color and sizes
  btnColor = color(#008CBA);
  highlightColor = color(#00bfff);
  
  //Set sizes of buttons
  btnWidth = 150;
  btnHeight = 75;
  
  //Set position of buttons
  btnY = 600;
  
  nbrOfBtns = 5;
  
  //setting start pos
  btnX = new int[nbrOfBtns];
  btnX[0] = 0 + ((1280-(btnWidth*5+40))/2);
  for(int i = 1; i < btnX.length; i++){
    btnX[i] = btnX[i-1] + btnWidth + 10;
  }
  
  //initializing hover states
  btnHover = new boolean[nbrOfBtns];
  for(int i = 0; i < btnHover.length; i++){
    btnHover[i] = false;
  }
  

  //Displaying and setting Serial port to chosen USB
  println("Available serial ports:");
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  
  //Descriptions
  exerciseDescs = new String[5];
  exerciseDescs[0] = "Make an electronic product code (EPC) which allows your RFID to open a door" + "\n \n" + "The door accepts key #12, #34, #86, #42 and #05" + "\n \n"
+"The manual tells that the door reads RFID with code packages 2";
  exerciseDescs[1] = "Steal a credit card by making an RFID tag which is a copy of it" + "\n \n" + "The credit card uses code package 2 from the producer and is encrypted so that it only uses serial keys with a singel digit in them";
  exerciseDescs[2] = "Open an unknown lock, using producer package 1, by unlocking it using a key containing a prime number";
  exerciseDescs[3] = "Make it so that your RFID can open a safe" + "\n \n" + "The safe accepts key serial 5262773D595" + "\n \n" + "The product package for opening this safe must include letters in its second and third part";
  exerciseDescs[4] = "Open a door which accepts even numbers higher than 50" + "\n \n" + "The door uses producer package 1 to read RFID's";
  
  //Default exercise is the first one
  chosenExercise = 0;
  
  setEndState(0);
  
  //Create win sound from: https://www.youtube.com/watch?v=P3ALwKeSEYs
}

void draw(){
  //Reading data from the arduino over serial. Will set the endstate.
  while(myPort.available() > 0){
    int inByte = myPort.read();
    println(inByte);
    
    //  received end state
    if(inByte == 53 || inByte == 54){
      setEndState(inByte);
    }
  }
  
  //Update hover status of buttons
  updateHover(mouseX, mouseY);
  
  //Forcing a reset to remove old text
  removeOldText();
  
  //Update exercise description
  updateDesc();
  
  //Updates the message displaying whether the player won or not
  updateEndMessage();
  
  //Draw Buttons
  for(int i = 0; i < btnX.length; i++){
    if(btnHover[i]){
      fill(highlightColor);  
    }else{
      fill(btnColor);  
    }
    rect(btnX[i], btnY, btnWidth, btnHeight);
  }
  
  //Set text on buttons
  fill(255,255,255);
  textSize(24);
  textAlign(CENTER, CENTER);
  for(int i = 0; i < btnX.length; i++){
    text("Exercise " + (i+1),btnX[i],btnY,btnWidth,btnHeight);
  }  
}

void updateDesc(){
  textSize(32);
  textAlign(LEFT, TOP);
  String text = exerciseDescs[chosenExercise]; 
  fill(0,0,0);
  int boxWidth = 600;
  int boxHeight = 430;
  
  //draw new text
  text(text, 0+((1280-boxWidth)/2), 10, boxWidth, boxHeight);
}

//force a reset to remove old text
void removeOldText(){ 
  background(0);
  background(255,255,255);
}

//Display win or fail
void setEndState(int state){
  //5 represents win state
  endState = state;
  if(endState == 53){
    winFile.play();
  }else if(endState == 54){
    failFile.play();
  }
    
}

//Updates the message according to the endstate
void updateEndMessage(){
  int endMessageWidth = 600;
  int endMessageHeight = 100;
  
  int endMessageX = 0+((1280-endMessageWidth)/2);
  int endMessageY = 460;
  
  if(endState == 53){
    fill(50,205,50);
    text("The tag is correct and the lock was opened", endMessageX, endMessageY, endMessageWidth, endMessageHeight);
  }else if(endState == 54){
    fill(#FF0000);
    text("The tag is incorrect and the lock was not opened", endMessageX, endMessageY, endMessageWidth, endMessageHeight);
  }
}

void setExercise(int exercise){
  chosenExercise=exercise;
}

void updateHover(int x, int y){
  for(int i = 0; i < btnX.length; i++){
    if(x >= btnX[i] && x <= btnX[i]+btnWidth && y >= btnY && y <= btnY + btnHeight ){
      btnHover[i] = true;
    }else{
      btnHover[i] = false;
    }
  }
}

void mousePressed(){
  for(int i = 0; i < btnHover.length; i++){
    if(btnHover[i]){
      setExercise(i);
      setEndState(0);
      sendNewExercise(i);
    }
  }
}

//Sends new exercise to arduino
void sendNewExercise(int exercise){
  myPort.write(exercise);
}