#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define buttonPin 5
#define dacpin A14
#define ADCpin A0  
#define PortPin A1
#define digPin 16

float prtvalue = 0;

uint8_t set1 = 0;
uint8_t set2 = 0;
uint8_t set3 = 0;

 uint8_t selection = 0;

  char ch = 0;
  uint8_t state = 0;
  uint8_t value = 0;
  static uint32_t previoustimebutton_ms = 0;  
  uint16_t buttonstate = 0;   

  int16_t count = 30; 

int centre = 0;
int radius = 0;
const float pie =3.1415;

void ISR();
void serial_com();
void mapping_select();
void set();


void Initialize();
void menu();

void osci_mode();
void funcgen_mode();
void Logic_mode();


void square_mode();
void triangle_mode();
void sin_mode();

void PrintInfo(uint16_t DAC_value, boolean digValue);
  
  enum states {
    WELCOME ,
    Menu,
    Osci,
    Function,
    Logicanalyser,
    Sinwave,
    Squarewave,
    Triangle,
  };

  states currentstate = WELCOME;

void setup()
{

pinMode(buttonPin, INPUT_PULLUP);
pinMode(dacpin,OUTPUT);
pinMode(ADCpin,INPUT);
pinMode( PortPin,INPUT);
pinMode(digPin, INPUT);
attachInterrupt(buttonPin,ISR,FALLING);

Serial.begin(9600);

//display.begin(SSD1306_SWITCHCAPVCC, 0X3C);

analogWriteResolution(10);
analogWriteResolution(10);

 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 error"));
    for(;;); 
  }

  display.clearDisplay();

}

void loop()
{
   serial_com();

   ISR();

   set();

   mapping_select();


  switch (currentstate)
  {
    case WELCOME:
    //serial.println("Start");
    Initialize();

    if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Menu ;
      buttonstate = 0;
  }
    break;

    case Menu:
    menu();

    if(set1 == 1 || state == 1){

      display.clearDisplay(); 
      currentstate = Osci ;

  }

   if(set2 == 1 || state == 2){

      display.clearDisplay(); 
      currentstate = Function ;

  }

     if(set3 == 1 || state == 3){

      display.clearDisplay(); 
      currentstate = Logicanalyser ;

  }

  
    if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = WELCOME ;
      buttonstate = 0;
  }
  break;
   
  case Function:
    menu();

    if(set1 == 1 || state == 4){

      display.clearDisplay(); 
      currentstate = Sinwave ;

  }

   if(set2 == 1 || state == 5){

      display.clearDisplay(); 
      currentstate = Squarewave ;

  }

     if(set3 == 1 || state == 6){

      display.clearDisplay(); 
      currentstate = Triangle ;

  }
  break;
  
   

  case  Osci :
  osci_mode();
  
      if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Menu ;
      buttonstate = 0;
  }
  break;

   case  Logicanalyser :
  Logic_mode();
      if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Menu ;
      buttonstate = 0;
  }
  break;

  case Sinwave:
  sin_mode();
  
      if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Function ;
      buttonstate = 0;
  }
  break;

  case  Squarewave :
  square_mode();
  
      if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Function ;
      buttonstate = 0;
  }
  break;

  case  Triangle :
  triangle_mode();
  
      if(buttonstate == 1 || state == 0){

      display.clearDisplay(); 
      currentstate = Function ;
      buttonstate = 0;
  }
  break;
    
  }
}



void Initialize(){

  // Clear the buffer.
    display.clearDisplay();
    
    // Display bitmap
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("WELCOME");
display.println("     ");
display.setTextSize(1);
display.setCursor(0,20);
display.println("press the button or press 1");
display.display();


}

void menu(){



display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("Menu");
display.setTextSize(1);
display.setCursor(10,10);
display.print("Logic Analyser");
display.setCursor(10,15);
display.print(" Function Generator");
display.setCursor(10,20);
display.print("2");
display.display();
display.setCursor(10,20);
display.print("Go back");
display.display();
//delay(2000);


}


void funcgen_mode(){

serial_com();

ISR();

mapping_select();

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("Fungen Mode");
display.setTextSize(1);
display.setCursor(10,10);
display.print("1.sinwave_mode");
display.setCursor(10,15);
display.print("2.squarewave_mode");
display.setCursor(10,20);
display.print("3.Trianglewave_mode");
display.display();
display.setCursor(10,20);
display.print("0.Go back");
display.display();

}
void osci_mode()
{
  display.clearDisplay();                                      // clears display
  display.drawRect(0, 0, 120, 64, WHITE);                      // draws border
  display.drawLine(0,30,120,30,WHITE);                         // draws grid horizontal center
  display.drawLine(30,0,30,64,WHITE);                          // draws grid vertical first
  display.drawLine(60,0,60,64,WHITE);                          // draws grid vertical second
  display.drawLine(90,0,90,64,WHITE);                         // draws grid vertical third
    
    display.setCursor(95,34);                                   // axis labels
    display.print("t(ms)");
    display.setCursor(0,0);
    display.print("3.3V");
    display.setCursor(0,32);
    display.print("0");
    display.display();
                                       
  
for(int x=0;x<120;x++)
    {
     
   int sensorValue = analogRead(A0);                                // read the input on analog pin 0:
  float voltage = sensorValue * (3.3 / 1023.0);                     // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
  voltage = 32-(voltage*7);                                         // y axis value: multiplied with 7 to scale y value 
  display.drawPixel(x,voltage,WHITE);                               // draws each pixel 
    display.display();                                              // displays new screen information
  
    }
  
}



void Logic_mode(){
  serial_com();
  uint8_t logic_analyzer(uint8_t frame);
  
    display.clearDisplay();
  // Serial.println(" Bit pattern is: ");
    Serial.println(ch, BIN);
    display.setCursor(28,28);
    display.println(ch,BIN);
    display.setTextSize(1);
    display.display();

}

void sin_mode(){

 


  
  display.drawLine(0,30,120,30,WHITE);                         // draws x axis
  display.drawLine(0,0,120,64,WHITE);                          // draws y axis
    
    display.setCursor(95,34);                                   // axis labels
    display.print("t(ms)");
    display.setCursor(0,0);
    display.print("3.3V");
    display.setCursor(0,32);
    display.print("0");
    display.display();                             
  
for (int i=0; i<120; i++)                                   // draws 120 pixels per loop
   { 
    float Angle = i*3 ;                                        // 120 X 3 = 360°
    int a = (centre - (sin(Angle * (pie / 180)) * radius));    // Pi/180 converts degrees to radians
    //Serial.println(a);

    display.drawPixel(i,a,WHITE);                              // draws each pixel for Sine wave
    display.display();                                         // displays new screen information
  }

}


void triangle_mode(){

   display.drawLine(0,64,120,64,WHITE);                         // draws x axis
   display.drawLine(0,0,0,64,WHITE);                            // draws y axis
    
    display.setCursor(110,60);                                  // axis labels
    display.print("t(ms)");
    display.setCursor(0,0);
    display.print("3.3V");
    display.setCursor(0,64);
    display.print("0");
    display.display();  

    //UP
   for(int x =0; x<=(4*count); x++)
  { for (uint16_t i = 0; i < count; i++)
    {
        analogWrite(dacpin,i);
        display.drawPixel(x,i,WHITE);                              // draws each pixel  
    }
    
    //DOWN
    for (uint16_t i = count; i > 0; i--)
    {
        analogWrite(dacpin,i);
        display.drawPixel(x,i,WHITE);                              // draws each pixel 
    }
  }                        
}


void square_mode(){

 /* for(uint16_t j = 0; j<120 ; j++)
  {
    
  }*/

      
}

 void Serial_com(){
  if( Serial.available())
  {
    

    if(ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
    {
       value = (value * 10) + (ch - '0'); // yes, accumulate the value
    }
    else if (ch == 10)  // is the character the newline character
    {
       state = value;  // set blinkrate to the accumulated value
       value = 0; // reset val to 0 ready for the next sequence of digits
    }
   }
  }


  void mapping_select(){

   
    prtvalue = analogRead(PortPin); 
    selection = map( prtvalue,0,1024,0,3);

  }


 void ISR()                                                                // Interrupt function
{
    uint8_t debounce_Time = 0;  
  uint32_t currenttimebutton_ms = millis();                               // Variable for debouncing
   if((currenttimebutton_ms - previoustimebutton_ms) >= debounce_Time) // Code inside loop only executes if buttonpress time is greater than debounce delay_ms
  {

    buttonstate = !buttonstate;
    previoustimebutton_ms = currenttimebutton_ms;
   buttonstate = buttonstate + 1;
  }  

}



void set(){

  mapping_select();

  ISR();

if (selection == 1 && buttonstate == 1)
{
  set1 = 1;
}
else
{
 set1 = 0;
}

if (selection == 2 && buttonstate == 1)
{
  set2 = 1;
}
else
{
 
 set2 = 0;

}

if (selection == 3 && buttonstate == 1)
{
  set3 = 1;
}
else
{
 set3 = 0;
}

}

void back(){

}

void PrintInfo(uint16_t DAC_value, boolean digValue){
        DAC_value = map(DAC_value, 0, 1023, 0, 3300); //map mv
        Serial.print((float)DAC_value);
        Serial.print(",");
        Serial.println(digValue * 3300);
        Serial.flush();
}

