/*Created 7 July 2018
By Victor Kumbol
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h> //import libraries for LCD screen
#include <SD.h> //import the SD Card library
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27,16,2);


int count = 0; //this variable will store the number of beam breaks
int threshold = 400; //Threshold for detecting IR radiation.This sets the sensitivity of the sensors
long runTime = 0; // this variable records the duration of the current test
long syncTime = 0; //this variable stores the last time the data was stored ot the SD card

File logfile; // the logging file


const long SYNC_INTERVAL = 60000; //mills between calls to flush()
const int chipSelect = 4; //the output pin for the SD card

String Sensor; //this stores the string type of the current sensor
String Count; //this variable stores the string type of the current beam-break count

int minutes;
int seconds;
int errors = false;

 //rows and cols will define the size of the array that stores pin assignments for the IR sensors
const int rows = 2;
const int cols = 8;


int SensorMatrix[rows][cols] = {
  // This matrix will hold the pin assignments for the IR sensors
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
pinMode(4, OUTPUT); // set the default chip select pin to output
initialize();
}


void loop() {
scan_sensors(); //call function to scan the IR sensors
display(); //call function to display results on LCD screen
log_data(minutes, count);  //call funtion to store results to SD card
}

//This function will initialize the IR sensors, lcd display and data logger to ensure they are working properly
void initialize() {
//initialize lcd screen for display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Booting system");
  delay(5000);

//Test all the sensors and report an error if any of them isn't working.
  lcd.clear();
  lcd.print("Testing sensors");
  delay(5000);

  for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
      SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
      if (SensorStateMatrix[i][j] < threshold){
        // if the reading from a sensor < threshold, toggle errors as true.
        errors = true;
        delay(20);
        }
      }
    }

    if (errors) {
      error("IR sensors faulty"); //report errors with sensors if any
    }
    else {
      lcd.clear();
      lcd.print("IR sensors OK");
      delay(2000);
    }

      // initialize the SD card
      Serial.print("Testing SD card.....");
      lcd.clear();
      lcd.print("Testing SD card");
      delay(5000);
      // see if the card is present and can be initialized:
      if (!SD.begin(chipSelect)) {
        error("SD card failed"); //report error with SD card if detected
      }
      Serial.println("SD card OK");
      lcd.clear();
      lcd.print("SD card OK");
      delay(2000);

      // create a new file
      char filename[] = "LOGGER00.CSV";
      for (uint8_t i = 0; i < 100; i++) {
        filename[6] = i/10 + '0';
        filename[7] = i%10 + '0';
        if (! SD.exists(filename)) {
          // only open a new file if it doesn't exist
          logfile = SD.open(filename, FILE_WRITE);
          logfile.println("time (min),activity count");
          break;  // leave the loop!
        }
      }

      if (! logfile) {
        error("file not created"); //report error with creating a file, if any
      }

      Serial.print("Logging to: ");
      Serial.println(filename);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Logging to: ");
      lcd.setCursor(0,1);
      lcd.print(filename);
      delay(2000);

      Serial.println("time (min),activity count");

    lcd.clear();
    lcd.print("Setup Complete");
    delay(2000);
    lcd.clear();

}//close initialize


void scan_sensors(){
  //this function will scan all the sensors one after the other to detect beam breaks
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
  SensorStateMatrix[i][j] = analogRead(SensorMatrix[i][j]); //read the current value of the corresponding sensor
  if (SensorStateMatrix[i][j] <= threshold && lastSensorStateMatrix[i][j] > threshold) {
  // if the beam was just broken (i.e. the sensor value dropped below the threshold) increment count and record the time
    count += 1;
    Sensor = String(SensorMatrix[i][j] + 1);
  }
  lastSensorStateMatrix[i][j] = SensorStateMatrix[i][j];
 delay(2);
    }

  }
     delay(50);
return;
}


void display() {
  //display total count of beam breaks
  runTime = millis();
  minutes = runTime/60000;
  seconds = (runTime%60000)/1000;
  lcd.setCursor(0,0);
  lcd.print("Time:" + String(minutes) + "min " + String(seconds) + "s");
  lcd.setCursor(0,1);
  lcd.print("Count:" + String(count));
  return;
}

void error(char *str){
  Serial.print("Error: ");
  Serial.println(str);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Error: ");
  lcd.setCursor(0,1);
  lcd.print(str);
  while(1);
}

void log_data (int a, int b){
  //check if the time interval after the last data logging session is equal to the sync interval
  if ((millis() - syncTime) < SYNC_INTERVAL) {
    return;
  }

  if (a < 1){
    a=1;
    }

  // log minutes since starting to the SD card
  logfile.print(String(a));           // milliseconds since start
  logfile.print(", ");
  Serial.print(String(a));         // milliseconds since start
  Serial.print(", ");

//log the activity count to the SD card
  logfile.print(String(b));
  logfile.println();
  Serial.print(String(b));
  Serial.println();
  logfile.flush();
  syncTime = millis();
}
