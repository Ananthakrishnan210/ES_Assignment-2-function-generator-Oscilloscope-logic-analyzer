# ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer
ES_Assignment-2/function generator/Oscilloscope/logic analyzer using teensy 3.2 board and uses OLED for display
#**LOGIC ANALYZER,MINIMAL OSCILLOSCOPE and FUNCTION GENERATOR-ES_Embedded System** 

## AIM

The aim of this project  is to develop a prototype of a system that can generate and run the functions; Minimal Oscilloscope,Function generator (Sine Function,Triangle Function and Square Function) and Logic Analyzer.



## INTRODUCTION

The aim of this project  is to develop a prototype of a system that can generate and run the functions; Minimal Oscilloscope,Function generator (Sine Function,Triangle Function and Square Function) and Logic Analyzer using Teensy 3.2 Microcontroller and a OLED.

We have to mae these followings to be :-

• One channel oscilloscope (0V - 3.3V) using the uC ADC peripheral 

• One channel function generator using the uC DAC with the option to select between at least a square, triangle and sin signal) 

•One channel logic analyzer, that allows for decoding of a 9600 baud serial frame 

• When acting in one of the above-mentioned modes, the relevant signals should be streamed out in “real-time” via UART(-> USB) to a connected PC and visualized using a serial plotter and in parallel displayed on the provided OLED display

 • It should be possible to control the different functions(modes) via connected push-buttons and in parallel via commands send from the PC to the uC via USB(->UART) .

• The system should be structured and implemented as a finite state machine



## COMPONENTS DESCRIPTION

1. Teensy 3.1/3.2
2. Mini Push Button
3. Connecting Wires
4. Breadboard
5. OLED SDD1306 
6. Potentiometer

## CIRCUIT
In this circuit , Teensy board connected to  the bread board .And , 

*>mini push button connected  pin 5 and GND.*

*>Potentiometer connected to Vcc ,GND ,Pin 14.*

*>OLED Display connected to Vcc,GND,Pin 18(SDA) ,Pin 19(SCL)*

*>Pin A14 (DAC pin) and pin 14 connected
(short) to read ADC out*


![enter image description here](https://github.com/Ananthakrishnan210/ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer/blob/master/Breadboardconnection.jpg)

## DESIGN

This system is the combination of some special function in micro controller programming ; like Interrupt,Mapping,Serial communication, Function generator mode creation ,etc.

In this, am using UART-PC USB communication to complete the serial communication in the system also used to plot the graph which we generate in teensy 3.2 with the Function generator modes. And, we use A14 / DAC pin to generate the required functions.And, we can took the same output in the OLED display also. OLED  is the interface that we used in this project . 

Also, am using a push button and potentiometer for the selection and activation of each mode and am using the same push button to came back to the previous window  from the current window, for this function compares two variables from serial communication and push button ,Potentiometer (mapping).

We had a Interrupt function for the push button , which will interrupt the main program and switch it into a special function and get back to the main function.


 
### Finite State Machine 
One of the main method we used in this project is the use of Finite state machine(Moore Function)

### **State**
***Initialize**: This the first ?open screen of the system
***Menu**: In this mode ,we can we 3 main condition for the user.
***Osci** :Mode: Its a function that runs the minimal oscilloscope
***Function Generator**: generate the 3 main standard functions .
***Square Wave** :Generate square wave by controller to DAC.
***Sine Wave** :Generate sine wave by controller to DAC.
***Triangle Wave** :Generate triangle wave by controller to DAC.

### **EVENT**

 - Serial input(selection)
 - button press and port1
 - button press and port2
 - button press and port3
 - Button Press
 - mapping_select
 -
### **ACTIONS**

 - Oscilloscope
 - Logic Ananlysis
 - Square Wave Signal
 - Sine Wave Signal
 - Triangle  Wave Signal

## STATE DIAGRAM

![enter image description here](https://github.com/Ananthakrishnan210/ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer/blob/master/image.png)

## WAVE FORM OUTPUT IN SERIAL PLOT

### SQUARE WAVE

![enter image description here](https://github.com/Ananthakrishnan210/ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer/blob/master/Capture.PNG3.PNG)

### TRIANGLE WAVE

![enter image description here](https://github.com/Ananthakrishnan210/ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer/blob/master/Capture.PNG)

### OSCILLOSCOPE OUTPUT WAVEFORM

![enter image description here](https://github.com/Ananthakrishnan210/ES_Assignment-2-function-generator-Oscilloscope-logic-analyzer/blob/master/Capture.PNG7.PNG)

## OUTPUT

The Output wave we can observe with application -Serial plot and in the display, almost same as the expected result ;except in logic Analyzer . Logic Analyzer conversion was wrong after the calculation.



## CONCLUSION

The project was a more knowledge sounded and it give more practical experience in every electrical and electronic system into a more finite state machine terms . And, also give more clear picture in the working of a analyzer ,function generator and Oscilloscope.


## REFERENCE
1._[Pixel mapping] 16 DMA, how to use them ?_ (n.d.). PJRC (Teensy) Forum. [https://forum.pjrc.com/threads/55193-Pixel-mapping-16-DMA-how-to-use-them](https://forum.pjrc.com/threads/55193-Pixel-mapping-16-DMA-how-to-use-them)

_2.Java enum-based state machine (FSM): Passing in events_. (n.d.). Stack Overflow. [https://stackoverflow.com/questions/25581176/java-enum-based-state-machine-fsm-passing-in-events](https://stackoverflow.com/questions/25581176/java-enum-based-state-machine-fsm-passing-in-events)

3.Slack. (n.d.). _Slack_. [https://weltecmechatronics.slack.com/archives/C0104E0GW1E/p1591247434001000](https://weltecmechatronics.slack.com/archives/C0104E0GW1E/p1591247434001000)

4.[https://www.youtube.com/playlist?list=PLEc1sXYwnTZm9fBVoHYQ-0KwB1ganOyKn](https://www.youtube.com/playlist?list=PLEc1sXYwnTZm9fBVoHYQ-0KwB1ganOyKn)
5.Teensyduino: Using the UART (real serial) with Teensy on the Arduino IDE. (2020). Retrieved from [https://www.pjrc.com/teensy/td_uart.html](https://www.pjrc.com/teensy/td_uart.html)
6.To know the using of serial communication and ASCII converstion.
[https://www.oreilly.com/ library/view/arduino-cookbook/9781449399368/ch04.html](https://www.oreilly.com/library/view/arduino-cookbook/9781449399368/ch04.html)















