#include <SoftwareSerial.h>
int volume;               //variable to read the value from Sound sensor
int inputPin = 2;        // choose the input pin (for PIR sensor)
int buzzerPin = 9;      //choose the input pin (for buzzer)
int val = 0;           //variable to read the value from PIR sensor
SoftwareSerial sim(10, 11);  //10-Rx,11-Tx used for communication
String number = "+911234567890";       // mobile number to which alert message has to be sent
void setup() {
  delay(7000);                       //delay for 7 seconds to make sure the modules get the signal
  pinMode(inputPin, INPUT);         // declare sensor as input
  pinMode(buzzerPin, OUTPUT);      // declare the pin as output mode
  Serial.begin(9600);             // Serial port begin  (or) Setting the baud rate of Serial Monitor (Arduino)
  sim.begin(9600);               // Setting the baud rate of GSM Module
}
void loop() {
  volume = analogRead(A0);       // Reads the value from the Analog PIN A0 - here we connect sound sensor out pin to A0
  val = digitalRead(inputPin);  // read input value (from pin 2)
  Serial.println(volume);      //Serial print level
  if (volume > 50)
  {
    Serial.println(val);
    if (val > 0)   // check the existence of person
    {
      Serial.println("Motion detected!");
      tone(buzzerPin, 50, 1000);    // used to activate the buzzer with frequency and time 
      val = 0;
    }
    SendMessage();  // calling the function
    delay(1000);
  }
  delay(1000);
}
void SendMessage()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");      //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r");   //Mobile phone number to send message
  delay(1000);
  String SMS = "Hello, how are you?";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);       // ASCII code of CTRL+Z
  delay(1000);
}
