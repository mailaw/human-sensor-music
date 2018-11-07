var serial;
var portName = '/dev/cu.usbmodem1421';
//var inData; //sensor values

var sample1, beat1, strings1;
var serialInArray = new Array(3);
var serialCount = 0;                 // A count of how many bytes we receive
var xpos, ypos;                // Starting position of the ball
var firstContact = false;        // Whether we've heard from the microcontroller
var circleColor = 255;
 
function preload() {
  sample1 = loadSound('samples/DOLCE_VITA.wav');
  beat1 = loadSound('samples/yae_beat.wav');
  strings1 = loadSound('samples/grand_strings.wav');
}

function setup() {
  createCanvas(800,400);
  serial = new p5.SerialPort();
 
  serial.on('list', printList); //callback for serialport list event
  serial.on('data', serialEvent); //callback for new data coming in
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
  
  serial.list();
  serial.open(portName); //open port
 
}

function draw() {
  background("#2307AF");
  fill(circleColor);
  ellipse(xpos, ypos, 20, 20);
  /*text("sensor", 20, 20);
  
  if (inByte == 1 || inByte == 0){
    text("sensor value: " + inByte, 80, 20);
  } */ 
}

/*function serialEvent() { //responds to new data
  console.log(inData); //inData is a number...
  inData = Number(serial.read());
}*/

function serialEvent(){
  //can choose to receive bytes or strings
  //var inByte = serial.read();
  
  //for now, try just strings
  var inString = serial.readStringUntil('\r\n');
  if (inString.length > 0 ) { //check for string
    if(inString !== 'hello') {
      var sensors = split(inString, ',');            // split the string on the commas
      if (sensors.length > 2) {                      // if there are three elements
        xpos = map(sensors[0], 250, 410, 0,width);   // element 0 is the locH
        ypos = map(sensors[1], 250, 410, 0, height); // element 1 is the locV
        circleColor = 255 - (sensors[2] * 255);      // element 2 is the button
       }
     }
     serial.write('x');
  }
  /*
  if (firstContact == false) {
      if (inByte == 'A') {
        serial.clear();          // clear the serial port buffer
        firstContact = true;     // you've had first contact from the microcontroller
        serial.write('A');       // ask for more
      }
  } else {
      // Add the latest byte from the serial port to array:
      serialInArray[serialCount] = inByte;
      serialCount++;
      console.log("one",serialInArray[0]);
      // If we have 3 bytes:
      if (serialCount > 2 ) {
        console.log("one",serialInArray[0]);
        console.log("two",serialInArray[1]);
        xpos = serialInArray[0];
        ypos = serialInArray[1];
        fgcolor = serialInArray[2];

        // print the values (for debugging purposes only):
        console.log(xpos + "\t" + ypos + "\t" + fgcolor);

        // Send a capital A to request new sensor readings:
        serial.write('A');
        // Reset serialCount:
        serialCount = 0;
      }
    }*/
}


///PORT FUNCTIONS
function printList(portList){
  for (var i = 0; i < portList.length; i++){
    //display list the ocnsole
    console.log(i + " " + portList[i]);
  }
}

function serverConnected() {
  console.log('connected to server.');
}
 
function portOpen() {
  console.log('the serial port opened.')
}
 
function serialError(err) {
  console.log('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  console.log('The serial port closed.');
}

//SOUND FUNCTIONS
function pirSound(inData){
  if(inData == 1){
    sample1.play();
    //strings1.play();
    background(0,255,0);
  } else {
    beat1.stop();
    background("#2307AF");
  }
}
