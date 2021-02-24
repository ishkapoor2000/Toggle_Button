#include <EEPROM.h>

//Pin number declaration
int ledPin = 13;
int buttonPin = 2;

//Global variables
int toggleState;
int lastButtonState = 0;
long unsigned int lastPress;
int debounceTime = 20;
int counter;

void setup()
{
  //Pin modes declaration
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  //assign counter the value of 0 address
  counter = EEPROM.read(0); //EEPROM.read(address);
  //write a '0' to address '0'.This allows consecutive resets to reset the counter.
  EEPROM.write(0, 0);//EEPROM.write(address, value);
}

void loop()
{
  //Read the state of button and store it as buttonState(0 or 1)
  int buttonState = digitalRead(buttonPin);

  //if the time between the last buttonChange is greater than the debounceTime
  if ((millis() - lastPress) > debounceTime)
  {
    //update lastPress
  	lastPress = millis();

    //if button is pressed, and was released last change
    if (buttonState == 0 && lastButtonState == 1)
    {
      //toggle the LED state by mturn its current state to the opposite state	
      toggleState =! toggleState;
      counter++;
      EEPROM.write(0, counter);
      digitalWrite(ledPin, HIGH);
      lastButtonState = 0;
      Serial.print("Counter: ");
      Serial.println(counter);
    }

    //if button is pressed, and was pressed last change
    if (buttonState == 1 && lastButtonState == 0)
    {
      //record the last button state
      lastButtonState = 1;
      digitalWrite(ledPin, LOW);
    }

  }

}