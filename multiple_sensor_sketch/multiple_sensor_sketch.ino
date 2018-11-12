int ledPin = 13;

int pirPin = 9; //first sensor
int micPin = A1; //second sensor
int buttonPin = 4; //third sensor

int laserPin = 2; 

//int inByte = 0;         // incoming serial byte
int pirState = 0; //first
int micVal = 0; //second
int buttonState = 0; //third

int voltage = 0; //val for laser


void setup() 
{
  Serial.begin(9600); //configure serial connection
  while(Serial.available() < 0) {
    Serial.println("hello");
    delay(300);
  }
  pinMode (ledPin,OUTPUT); //use led as output interface
  
  pinMode (pirPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(micPin, INPUT);
  
  //pinMode (laserPin ,OUTPUT); // designating digital pin 2 for output
  //digitalWrite(laserPin ,LOW); // just making sure the laser is off at startup or reset

}
void loop () 
{
    if( Serial.available() > 0){
      int inByte = Serial.read();
      /*read sensor values*/
      mic();
      delay(10);
      pir();
      delay(10);
      //button();
      buttonState = map(digitalRead(buttonPin), 0, 1, 120, 255);
      Serial.println(buttonState);
      delay(10);
    }
   
}

void mic(){
  micVal = analogRead(micPin);
  //Serial.write(micVal);
  Serial.print(micVal);
  Serial.print(",");
}

void pir(){
  pirState = digitalRead(pirPin);
  //Serial.write(pirState);
  Serial.print(pirState);
  Serial.print(",");
  /*Serial.write(pirState);
  Serial.print("PIR");
  Serial.println(pirState);*/
  /*
  if (pirState == 1) { // check if input is high
    Serial.println(pirState);
    Serial.write(pirState);
    
    if(pirState == 0) {
      Serial.println("Motion detected");
      pirState = 1;
    }
 } else {
  Serial.println(pirState);
  Serial.write(pirState);
  if(pirState == 1){
    Serial.println("Motion ended");
    pirState = 0;
  }
 }*/
}

void button(){
  buttonState = map(digitalRead(buttonPin), 0, 1, 120, 255); //return either 120(pressed) or 255(not pressed)
  //Serial.write(buttonState);
  /*check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
   }*/
}

void laser() {
  digitalWrite(laserPin,HIGH); // turning the laser on
  voltage = analogRead(A0); //reading the voltage on A0 and storing the value received in "voltage"
  float voltage1 = voltage * (5.0 / 1023.0); // transforming the value stored in "voltage" to readable information
  
  Serial.print("the laser is ON and the voltage on the center pin is "); //sending that sentence to the serial monitor
  Serial.println(voltage1); // adding the value in voltage1 to the end of the sentence above and starting a new line on the monitor
  Serial.println(); // adding a blank line for readability
  delay(1000); // waiting for one second before continuing sketch
  
  
  digitalWrite(laserPin,LOW); // turning the laser off
  
  voltage = analogRead(A0); // reading the voltage on A0 and storing the value received in "voltage"
  float voltage2 = voltage * (5.0 / 1023.0); // transforming the value stored in "voltage" to readable information
  
  Serial.print("the laser is OFF and the voltage on the center pin is "); // sending that sentence to the serial monitor 
  Serial.println(voltage2); // adding the value in voltage2 to the end of the sentence above and starting a new line on the monitor
  Serial.println(); // adding a blank line for readability
  delay(1000); // waiting for one second before continuing sketch
  
  /* You can play with a couple of things with this sketch
   *  1.  you can play with the "delay" times, turning the laser on and off faster or slower
   *  2.  place a resistor in-line with the power to the module resulting in differant voltages 
   *      displaying on the serial monitor.
   */
   
}



