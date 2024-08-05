//These lines include necessary libraries. Wire.h is for I2C communication, LiquidCrystal_I2C.h is for controlling an I2C LCD, and Stepper.h is for controlling a stepper motor.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>  
const int stepsPerRevolution = 200;  // fit the number of steps per revolution
// for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 9,10,11,12);        //It is initialized with the number of steps per revolution and the pins (9, 10, 11, and 12) that the stepper motor is connected to.
LiquidCrystal_I2C lcd(0x27, 16, 2);                       //This line initializes an I2C-connected LCD. The parameters passed include the LCD's I2C address (0x27), the number of columns (16), and the number of rows (2).
int stepCount = 0;                                        // This variable is initialized to keep track of the number of steps the motor has taken.

//In the setup function, the LCD is initialized, and some initial text is displayed on it.
void setup() {
  lcd.begin();                                                  // Initialize the LCD
  lcd.setCursor(1, 0);                                         // define below message's start point, and Set the LCD cursor to column 1, row 0
  lcd.print("Stepping Motor");                               // Display "Stepping Motor"
  lcd.setCursor(0, 1);                                      // Set the cursor to column 0, row 1
  lcd.print("Speed: ");                                    // Display "Speed: "
}


//The loop function is the main part of the code that runs repeatedly. 
//It reads the analog value from the potentiometer (connected to A0), maps this value to a motor speed between 0 and 100, sets the motor speed if it's greater than 0, and moves the stepper motor one step (1/100th of a revolution)
//It also updates the LCD with the current motor speed.



void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);                              // Read the analog value from the potentiometer connected to A0
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1024, 0, 100);           // Map the sensor value to a motor speed range (0-100)
  if (motorSpeed > 0) {                                            
    myStepper.setSpeed(motorSpeed);                               // set the fan (stepper motor) speed
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution/100);                       // Move the motor one step (1/100 of a revolution)
  }
  lcd.setCursor(8, 1);                                            // Set the LCD cursor to column 8, row 1
  lcd.print(motorSpeed);                                          // Display the motor speed on the LCD
  

}