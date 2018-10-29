var serial;
var portName = '/dev/cu.usbmodem1421';
var inData; //sensor values

function setup() {
  createCanvas(400,400);
  serial = new p5.SerialPort();
  
  serial.on('list', printList); //callback for serialport list event
  serial.on('data', serialEvent); //callback for new data coming in
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
  
  serial.list();
  serial.open(portName); //open port
}

function serialEvent() { //responds to new data
  inData = Number(serial.read());
  //console.log(typeof inData); //inData is a number...
}

function draw() {
  background("#2307AF");
  fill(255);
  // ellipse(sensorValue,height/2,20,20);
  if (inData == 1 || inData == 0){
    text("sensor value: " + inData, 20, 20);
  }
}

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
