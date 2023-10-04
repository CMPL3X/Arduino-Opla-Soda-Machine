# Arduino-Opla-Soda-Machine


❗You can find the instruction and videos in my arduino project hub or hackster.io page❗


**Things used in this project**
Arduino Oplà IoT Kit
NeoPixel Ring: WS2812 5050 RGB LED	
Adafruit Peristaltic Liquid Pump x2
Or Air Pump x2
Hook Up Wire Kit, 22 AWG	
DC Power Connector, Jack (If 12v)
Adafruit Soft Tubing
Adafruit Fitting Connector (Optional)
Amazon Alexa Official Arduino Skill
Arduino Web Editor	
Arduino IoT Cloud
Hand tools and fabrication machines
Soldering iron (generic)	
Multitool, Screwdriver
Wire Stripper & Cutter, 18-10 AWG / 0.75-4mm² Capacity Wires	

**About the project**

Problem :
We don't have a lot of options for smart soda machines. They usually don't work with smart homes. The ones we can buy are way too expensive and hard to maintain.

Soulution :
That's why i came up with an cheap DIY alternative. It works With Alexa. In this page you will find all the instructions to make it.

Result :
At the end you will have an amazing low cost soda machine that you will be able to connect to any smart home device by triggering routines. In Alexa app you can also set times to triger them. Soo you can set it to make you sodas at every morning! It will make your life way easier! You will be able to control it from anywere, because it's connected to arduino cloud.

Also you will learn new things/skills about IoT and Arduino! This will be a lot of fun!

**Code**

Now we can start coding. First you have to go to "Things" tab (In the IoT Cloud). Then open the thing you set up. Then press on "Sketch". Then press "Open full editor".

Now you can just grab my code below this page. You need to copy "SodaMachine" and "thingProperies" code in your tabs. The "Secret" will set automaticly.

Now you can set "// settings" at the top of my code. Now you have to set cup sizes. You need to connect pumps to electricity and with a timer time how long does it take to pour "half" and "full". M1 is motor 1 and M2 is motor 2. Its timed in milliseconds! You can also set the name for the drinks in 19 and 25 line. You can also set the light color in 29 line. It will change the entire theme of the interface.

Now the code is finnished. You will need to install arduino agent and now you can connect the opla and upload to it.
