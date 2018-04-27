int outPin = 13; // the pin number of the indicator LED
int outPinState = LOW; // the current state of the indicator LED
int count = 0; //this variable will store the number of beam breaks
int limit=50;                 //Threshold for detecting IR radiation

// the following variables are long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long outTime = 0; // the last time the output pin was toggled

 //rows and cols will define the size of the array
const int rows = 2;
const int cols = 8;#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int outPin = 13; // the pin number of the indicator LED
int count = 0; //this variable will store the number of beam breaks
int limit = 400; //Threshold for detecting IR radiation.
//The higher the threshold the higher the sensitivity
long outTime = 0; // the last time the beam was broken
long runTime; // how long the current test has been running for
String Pin;
String Count;

int minutes;
int seconds;
int errors = false;
 //rows and cols will define the size of the array
const int rows = 2;
const int cols = 8;


int SensorMatrix[rows][cols] = {
  // This matrix will hold the pin assignments for the Sensors
  {0, 1, 2, 3, 4, 5, 6, 7},
  {8, 9, 10, 11, 12, 13, 14, 15}
};

int SensorStateMatrix[rows][cols] = {
 // This matrix will store the current reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int lastSensorStateMatrix[rows][cols] = {
 // This matrix will store the previous reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};


void setup() {
Serial.begin(9600); //initialize serial monitor for writing
pinMode(outPin, OUTPUT); //set outPin as an output pin
initialize();
} //close setup()


void loop() {
scan_sensors();
display();
} //close loop()



void initialize() {
//This function will initialize the sensors and lcd display
//initialize lcd screen for display
  lcd.init();
  lcd.backlight();
  //Test all the sensors and report an error if any of them isn't working.
  Serial.println("Initialising sensors......");
  delay(2000);
  lcd.clear();
  lcd.print("Testing sensors.");
  for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
      SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
      // if sensor is working it should be reporting a reading > limit.
      Pin = String(SensorMatrix[i][j] + 1);
      if (SensorStateMatrix[i][j] > limit){
        Serial.print("Sensor " + Pin + " is working fine");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Testing sensors.");
        lcd.setCursor(0,1);
        lcd.print("Sensor " + Pin + " OK");
        delay(2000);
        }
      else {
        // if sensor is malfunctioning it should be reporting a reading <= limit.
        errors = true;
        Serial.print("ERROR");
        Serial.print("Sensor " + Pin + " faulty");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ERROR");
        lcd.setCursor(0,1);
        lcd.print("Sensor " + Pin + " faulty");
        delay(2000);
        }

      }//close for j

    }//close for i

    if (errors) {
      //error();
    }
  Serial.println("Initialisation complete");
  lcd.clear();
  lcd.print("Init complete");
  delay(2000);
  lcd.clear();
  return;
}//close initialize


void scan_sensors(){
  //this function will scan all the sensors one after the other to detect beam breaks
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
  SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
  // if the beam was just broken (i.e. the sensor value went from > limit to <= limit)
  if (SensorStateMatrix[i][j] <= limit && lastSensorStateMatrix[i][j] > limit) {
    count += 1;
    outTime = millis(); //remember the last time the beam was broken
    Pin = String(SensorMatrix[i][j] + 1);
    //display the last pin broken, the time it was broken and the total count on the serial monitor
    Serial.print("Pin broken= ");
    Serial.println(Pin);
    Serial.print("Beam break time = ");
    Serial.println(outTime);
    Serial.print("Total beam breaks = ");
    Serial.println(count);
  }
  lastSensorStateMatrix[i][j] = SensorStateMatrix[i][j];
 delay(2);
    }//close for j

  }//close for i
     delay(50);
return;
}

void display() {
  //display total count and last broken pin on lcd screen
  runTime = millis();
  minutes = runTime/60000;
  seconds = (runTime%60000)/1000;
  Count = String(count);
  lcd.setCursor(0,0);
  lcd.print("Runtime:" + String(minutes) + "min " + String(seconds) + "s");
  lcd.setCursor(0,1);
  lcd.print("Total count:" + Count);
  return;
}

void error(){
  //cli();
  while( true ){
    lcd.clear();
    lcd.print("System Error");
    delay(2000);
    lcd.clear();
    delay(1000);
  }
  return;
}



int SensorMatrix[rows][cols] = {
  // This matrix will hold the pin assignments for the Sensors
  {0, 1, 2, 3, 4, 5, 6, 7},
  {8, 9, 10, 11, 12, 13, 14, 15}
};

int SensorStateMatrix[rows][cols] = {
 // This matrix will store the current reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int lastSensorStateMatrix[rows][cols] = {
 // This matrix will store the previous reading from each sensor
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};


void setup() {
Serial.begin(9600); //initialize serial monitor for writing
pinMode(outPin, OUTPUT); //set outPin as an output pin
} //close setup()


void loop() {

  //this nested for loop will scan each IR sensor in sequence
  for(int i = 0; i < rows; i++){

    for(int j = 0; j < cols; j++){
  SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
  // if the beam was just broken (i.e. the sensor value went from > limit to <= limit) or restored (i.e. the sensor value went from <=limit to > limit),
  if (SensorStateMatrix[i][j] <= limit && lastSensorStateMatrix[i][j] > limit) {// || (SensorStateMatrix[i][j] > limit && lastSensorStateMatrix[i][j] <= limit)){
    outTime = millis(); //remember the last time the beam was broken or restored
    count += 1;
    Serial.print("Pin broken= ");
    Serial.println(SensorMatrix[i][j]);
    Serial.print("Beam break time = ");
    Serial.println(outTime);
    Serial.print("Total beam breaks = ");
    Serial.println(count);
    digitalWrite(outPin, HIGH);
    delay(1);
    digitalWrite(outPin, LOW);
  }
  lastSensorStateMatrix[i][j] = SensorStateMatrix[i][j];

    }//close for j

  }//close for i

} //close loop()
