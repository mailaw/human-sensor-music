#define trigPin 13
#define echoPin 12

void setup() {
// initialize serial communication at 9600 bits per second:
// pinMode(13, OUTPUT);

Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(12, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  
  //Ultrasounds input
  long duration, distance;
  int isBeat;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  isBeat = pulseIn(12, HIGH);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  /*
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
  */
  
  if(Serial.available()){  //id data is available to read
    int buttonVal = Serial.read(); // read the input on analog pin 0
    

    Serial.println(buttonVal);
    delay(100);
    Serial.println(isBeat); //replacing distance here
    Serial.write(isBeat); //send val as binary
    
  }
}
