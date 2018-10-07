import controlP5.*; //import ControlP5 library
import processing.serial.*;
import arb.soundcipher.*;

Serial myPort;        // The serial port
String val; //data recieved from serial port
int beatVal; //data recieved from serial port
int noteDynamic; //controlled by joystick

//Defining sounds n notes
SoundCipher sc = new SoundCipher();
int[] scale = {57, 57, 57, 57, 57, 57, 57, 57, 57};
float[] pitches = {60, 64, 67, 71};
float[] pitchesII = {80, 84, 87, 91};

ControlP5 cp5; //create ControlP5 object
PFont font;
int sliderValue = 100;
int sliderTicks1 = 100;
int sliderTicks2 = 30;
Slider sliderVolume;
int myColor = color(0,0,0);

Chart myChart;
int xPos = 1;         // horizontal position of the graph
float yPos = 0;
float height_old = 0;
float height_new = 0;
float inByte = 0;


void setup(){ //same as arduino program

  size(800, 600);    //window size, (width, height)
  printArray(Serial.list());   //prints all available serial ports
  frameRate(3);
  
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n'); 
    
  cp5 = new ControlP5(this);
  font = createFont("calibri light bold", 20);    // custom fonts for buttons and title
  
  cp5.printPublicMethodsFor(Chart.class);
  myChart = cp5.addChart("pulse")
  .setPosition(50, 50)
  .setSize(400, 200)
  .setRange(0, 200)
  .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
  ;

  myChart.getColor().setBackground(color(255, 100));
  myChart.addDataSet("beat");
  myChart.setColors("beat", color(255,0,255),color(255,0,0));
  myChart.setData("beat", new float[4]);
  myChart.addData("beat", inByte);
  myChart.setStrokeWeight(3);
  
  // add a vertical slider
  cp5.addSlider("sliderVolume")
     .setPosition(100,405)
     .setSize(200,20)
     .setRange(0,200)
     .setValue(128)
  ;
  /*
  cp5.addButton("Beat")     // name of button
    .setPosition(100, 50)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
  ;  
  cp5.addButton("Tempo")    
    .setPosition(100, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
  ;  */


}

//graphs the values of tempo
void serialEvent(Serial myPort) {
  //get byte
  int inByte = myPort.read();
  println("Beat:", inByte);
  
  yPos = height - inByte;
  if (xPos >= width) {
    xPos = 0;
    // clear the screen by resetting the background:
    background(#081640);
  } else {
    // increment the horizontal position for the next reading:
    xPos++;
  }
}

void sliderVolume(float theColor) {
  noteDynamic = color(theColor);
  println("a slider event. setting background to "+theColor);
}

void draw(){  //same as loop in arduino

  background(150, 0 , 150); // background color of window (r, g, b) or (0 to 255)
  //graph 
  stroke(#A8D9A7);
  line(xPos, height, xPos, yPos);
  if (myPort.available() > 0){
    beatVal = myPort.read();
  }
  //println("beat:", beatVal); //print it out in the console */

  background(sliderTicks1);
  fill(sliderValue);
  rect(0,0,width,100);
  
  fill(myColor);
  rect(0,380,width,70);
  
  fill(sliderTicks2);
  rect(0,450,width,50);
  
  //title to our window
  fill(0, 255, 0);               //text color (r, g, b)
  textFont(font);
  text("Human music", 80, 30);  // ("text", x coordinate, y coordinat)
  if (beatVal < 100) {
    sc.playChord(pitches, 80, 4);
  }
  else {
    sc.playChord(pitchesII, 65, 2);
  }

  // push: add data from right to left (last in)
  myChart.push("beat", beatVal);
  
} 

//this talks and sends to the arduino
void Beat(){
  myPort.write('h');
  print("h");
}
