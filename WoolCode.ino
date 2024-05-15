  /*
 Wool winder code


 Created May 8, 2024
 by Juan Vargas Aka. Sum
/Users/sum/Downloads/LiquidCrystal_I2C-1.1.2/examples/SerialDisplay/SerialDisplay.pde
 */

#include <Stepper.h>
#include <string.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//intalize functions
void WriteMessageScrollingBottom(String message);
void WriteMessageWrap(String message);
bool checkpoint1 = false;


const int stepsPerRevolution = 150;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 5,4, 10, 11:
Stepper myStepper(stepsPerRevolution, 5, 4, 10, 11);

// initialize liquid crystal panel at ports A4 and A5
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

  
void setup() 
{
  // set the speed at 900 rpm:
  
  myStepper.setSpeed(900);
  
  lcd.init();   // initialize the lcd panel of message system

  //set up system for the lcd screen
  lcd.backlight();
  lcd.begin(16, 2); 

  // initialize the serial port:
  Serial.begin(9600);
  delay("100");

  // general message shown in lcd and serial
  for (int i = 3; i > 0; --i){
  lcd.setCursor(0,0);
  lcd.print(i);
  WriteMessageScrollingBottom("Initalizing System...");

  }

  lcd.clear();
}

void loop() 
{
  // step forever
  myStepper.step(stepsPerRevolution);

  if (!checkpoint1) {
  WriteMessageWrap("welcome to woolwinder.exe!");
  checkpoint1 = true; 
  }
      //debug commands to serial interface
      if (Serial.available()) 
      {
        char receivedChar = Serial.read(); // Read a single character

        switch (receivedChar) {
          case '0':
            lcd.clear();
            break;
          case '1':
            lcd.clear();
            WriteMessageScrollingBottom("Never gonna give you up");
            // Add your code for option 1 here
            // Add your code for option 2 here
            checkpoint1 = false;
            break;
          case '2':
            lcd.clear();
            WriteMessageWrap("returning..");
            checkpoint1 = false;
            // Add your code for option 3 here
            break;

          default:
            break;
        }
      }

}


void WriteMessageWrap(String message)
{
  if(message.length() > 16)
  {
    String part1 = message.substring(0, 15);
    String part2 = message.substring(16);

    // Add spaces to the last word of part1
    int lastSpaceIndex = part1.lastIndexOf(' ');
    int spacesToAdd = 16 - part2.length();
    if (lastSpaceIndex != -1) {
      part2 = part1.substring(lastSpaceIndex + 1) + part2;
      part1 = part1.substring(0, lastSpaceIndex);
    }
    for (int i = 0; i < spacesToAdd; i++) {
    part2 += ' '; // Add spaces to the end of the string
    }

    // Print on the LCD
    lcd.setCursor(0, 0);
    lcd.print(part1);
    lcd.setCursor(0, 1);
    lcd.print(part2);

  }
  else
  {
    lcd.print(message);
  }
  Serial.println(message);
}
void WriteMessageScrollingBottom(String message)
{
  // Initialize the scrolling position
  int scrollPos = 0;
  // Check if the message length exceeds 16 characters
  if (message.length() > 16) 
  {
    // Continuously scroll the message
    while (scrollPos <= message.length() - 16)
    {
      String visiblePart = message.substring(scrollPos, scrollPos + 16);
      lcd.setCursor(0, 1);
      lcd.print(visiblePart);
      delay(500); // Adjust the scrolling speed (milliseconds)
      scrollPos++;
    }

  }else{
    lcd.print(message);
  }
  Serial.println(message);
}
