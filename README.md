# human-sensor-music
Creating music through the human interface using Arduino, Processing, p5.js

Setting Up

To run this project, you will need Processing, Arduino, and p5.serialcontrol.
On processing, sounds will be generated using the input provided from Arduino. The two applications talk to each other through the serial port, which is established through p5.serialcontrol.

After opening all applications, select the proper serial port in p5.serialcontrol. Typically this will look something like "/dev/cu.usbmodem1421." Then, run the Arduino sketch, upload it to the board, and run the Processing sketch to view the p5 application in your broswer.
