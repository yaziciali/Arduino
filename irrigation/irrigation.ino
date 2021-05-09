
// Include NewPing Library
#include "NewPing.h"
//#include <SoftwareSerial.h>
//SoftwareSerial BTserial(1, 0); // RX | TX
 
const long baudRate = 9600; 

const int Enable_A = 9;
const int Enable_B = 10;
const int inputA1 = 2;
const int inputA2 = 3;
const int inputB1 = 4;
const int inputB2 = 5;


const int sensor=A5; // Assigning analog pin A5 to variable 'sensor'
float tempc; //variable to store temperature in degree Celsius
float tempf; //variable to store temperature in Fahreinheit
float vout; //temporary variable to hold sensor reading

int val = 0; // = LOW, HIGH and LOW
int i = 0; // = Count
int j = 0; // = Count2
int delayi = 6000; // Wait duration
int maxi = 2; // = max incremental count
int speed1=80;
int maxdur1=2500; // maximum working duration
int maxdur2=4000; // maximum working duration
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(sensor,INPUT); // Configuring sensor pin as input

pinMode(Enable_A, OUTPUT);
pinMode(Enable_B, OUTPUT);
pinMode(inputA1, OUTPUT);
pinMode(inputA2, OUTPUT);
pinMode(inputB1, OUTPUT);
pinMode(inputB2, OUTPUT);

//---- A enable and B disable------//
digitalWrite(Enable_A, HIGH);
digitalWrite(Enable_B, LOW);
//----------Disable motors-----------//
digitalWrite(inputA1, LOW);
digitalWrite(inputA2, LOW);
digitalWrite(inputB1 , LOW);
digitalWrite(inputB2, LOW);
        val = LOW ;


////----------Speed up----------//
//for(j = 0; j < 150; j++)
//{
//analogWrite(Enable_A, j);
//            Serial.print(j);
//            Serial.println();
//delay(40);
//}
////----------Speed Down----------//
//for(j = 150; j > 0; j--)
//{
//analogWrite(Enable_A, j);
//            Serial.print(j);
//            Serial.println();
//delay(40);
//}

//analogWrite(Enable_A, speed1);
            analogWrite(Enable_A, speed1);
            digitalWrite(inputA1, LOW);
            digitalWrite(inputA2, HIGH);

              val = HIGH ;
             delay(maxdur2);
              analogWrite(Enable_A, LOW);
}
// the loop function runs over and over again forever
void loop() {


        oneCycle(); // Do something
        delay(delayi);

    
} // void loop


 
void oneCycle() { // Do something with the results.

    if (i >= maxi ) {

          switch(val) {
            case HIGH:
            analogWrite(Enable_A, speed1);
            digitalWrite(inputA1, HIGH);
            digitalWrite(inputA2, LOW);

              val = LOW ;
              delay(maxdur1);
              analogWrite(Enable_A, LOW);
              break;
            case LOW:
            analogWrite(Enable_A, speed1);
            digitalWrite(inputA1, LOW);
            digitalWrite(inputA2, HIGH);

              val = HIGH ;
             delay(maxdur2);
              analogWrite(Enable_A, LOW);
              
              break;
            default:
            analogWrite(Enable_A, speed1);
            digitalWrite(inputA1, LOW);
            digitalWrite(inputA2, HIGH);

              val = HIGH ;
             delay(maxdur2);
              analogWrite(Enable_A, LOW);

          }
    i=0;
    } // if (i >= maxi ) 
i=i+1;

            vout=analogRead(sensor); //Reading the value from sensor
            vout=(vout*500)/1023;
            tempc=vout; // Storing value in Degree Celsius
            tempf=(vout*1.8)+32; // Converting to Fahrenheit
            Serial.print("in DegreeC=");
            Serial.print("\t");
            Serial.print(tempc);
            Serial.print(" ");
            Serial.print("in Fahrenheit=");
            Serial.print("\t");
            Serial.print(tempf);
            Serial.println();

  //Serial.println();
}
