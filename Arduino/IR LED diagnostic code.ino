int outPin = 13; // the pin number of the indicator LED
int outPinState = LOW; // the current state of the indicator LED
int count = 0; //this variable will store the number of beam breaks
int limit=50;                 //Threshold for detecting IR radiation 

// the following variables are long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long outTime = 0; // the last time the output pin was toggled

 //rows and cols will define the size of the array 
const int rows = 2;
const int cols = 8;
String pin;

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
    //int pin_no = SensorMatrix[i][j]+ 1
    pin = String(SensorMatrix[i][j] + 1);
    Serial.print("Pin "); 
    Serial.println(pin);  
    Serial.print(" reading = "); 
    Serial.println(SensorStateMatrix[i][j]);  
    delay(5); 
  }
 
    }//close for j
     Serial.println("");  
     Serial.println("");  
     Serial.println("");  
     delay(5000);
  }//close for i
 


