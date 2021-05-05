
// Include NewPing Library
#include "NewPing.h"
//#include <SoftwareSerial.h>
//SoftwareSerial BTserial(1, 0); // RX | TX
 
const long baudRate = 9600; 
char c=' ';
boolean NL = true;


// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 10
#define ECHO_PIN 9

#define TRIGGER_PIN2 11
#define ECHO_PIN2 12

#define MOTOR_PIN2 2
#define MOTOR_PIN3 3
#define MOTOR_PIN4 4
#define MOTOR_PIN5 5
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 150 // Max distance in cm.
#define PING_INTERVAL 33 // Milliseconds between pings.
#define SONAR_NUM     2 // Number or sensors.
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.

NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE),
  NewPing(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE)
};
float dur, dist,dur2,dist2;

const int sensor=A5; // Assigning analog pin A5 to variable 'sensor'
float tempc; //variable to store temperature in degree Celsius
float tempf; //variable to store temperature in Fahreinheit
float vout; //temporary variable to hold sensor reading

int val = 0; // = LOW, HIGH and LOW

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(MOTOR_PIN5, OUTPUT);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2,INPUT);
  pinMode(sensor,INPUT); // Configuring sensor pin as input

//pinMode(5, OUTPUT);
//  pinMode(4,INPUT);

    pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;


 //  BTserial.begin(baudRate);  
 //   Serial.print("BTserial started at "); Serial.println(baudRate);
 //   Serial.println(" ");
}

// the loop function runs over and over again forever
void loop() {


 for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
  // The rest of your code would go here.


    
} // void loop

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (cm[i] > 0 ) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.println("cm ");
    
        if (cm[i] < 16){
          switch(val) {
            case HIGH:
              digitalWrite(MOTOR_PIN2, HIGH);
              digitalWrite(MOTOR_PIN3, LOW);
              digitalWrite(MOTOR_PIN4, HIGH);
              digitalWrite(MOTOR_PIN5, LOW);
              val = LOW ;
              delay(1000);
              break;
            case LOW:
              digitalWrite(MOTOR_PIN2, LOW);
              digitalWrite(MOTOR_PIN3, HIGH);
              digitalWrite(MOTOR_PIN4, LOW);
              digitalWrite(MOTOR_PIN5, HIGH);
              val = HIGH ;
              delay(1000);
              break;
            default:
            digitalWrite(MOTOR_PIN2, LOW);
            digitalWrite(MOTOR_PIN3, HIGH);

            digitalWrite(MOTOR_PIN4, LOW);
            digitalWrite(MOTOR_PIN5, HIGH);
            val = HIGH ;
              // code block
          }
        } //  if (cm[i] < 10){

           if(i % 2 == 0) {
           // cout<<num<<" is even";
            digitalWrite(7, HIGH);  
            digitalWrite(6, HIGH);
            digitalWrite(LED_BUILTIN, HIGH);
           } else {
           //cout<<num<<" is odd";
            digitalWrite(7, LOW);  
            digitalWrite(6, LOW);
            digitalWrite(LED_BUILTIN, LOW);
    
    
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

            
           } // if(currentSensor % 2 == 0)
    
    } // if (cm[i] > 0 ) {
  }
  //Serial.println();
}
