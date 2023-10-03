#include <SD.h>

int led1pin;    // initializing LED indicating PIR 1
int led2pin;    // initializing LED indicating PIR 2

int pir1pin;          // Digital Pin
int pir2pin;          // Digital Pin
bool pir1status;      // SETTING THE STATUS OF PIR #1 TO A BOOLEAN DATA TYPE
bool pir2status;      // SETTING THE STATUS OF PIR #2 TO A BOOLEAN DATA TYPE

float distance;   // This is your distance in meters (ft. * 0.3)

int count12; // count for walking from PIR 1 to PIR 2
int count21; // count for walking from PIR 2 to PIR 1

bool flag12; // check if walking from 1 to 2 has been triggered
bool flag21; // check if walking from 2 to 1 has been triggered
unsigned long initialTime = 0; // initial time of current walking pass
unsigned long elapsedTime = 0;
float totalTime = 0; // holds time difference between current time and total time
float checkTime = 0; // holds time difference between current time and total time (used as a check to avoid overwritting totalTime)

const int chipSelect = 10; // initializing chip

File logfile; // the logging file

void setup() {
  Serial.begin(115200); // setup serial terminal

  // initialize PIR and LED
  pinMode(led1pin, OUTPUT); pinMode(led2pin, OUTPUT);   // LEDs
  pinMode(pir1pin, INPUT); pinMode(pir2pin, INPUT);     // PIRs

  delay(10000); // PIR needs to warm up. Wait at least 10 seconds before starting

  // initialize the SD card
  Serial.print("\n Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  char filename[] = "path.csv"; // create a new file

  
  Serial.print("Logging to: ");
  Serial.println(filename);

  // logfile.begin();
  File logfile = SD.open(filename, FILE_WRITE);

  //HEADER 
  Serial.println("time, pir1, pir2, count 1 -> 2, count 2 -> 1, speed");
  logfile.println("time, pir1, pir2, count 1 -> 2, count 2 -> 1, speed");
  logfile.flush();
}

void loop() {
  unsigned long myTime = millis(); // Get current time

  // log current time-step to sd card and print to serial monitor
  logfile.print(myTime); logfile.print(", ");
  Serial.print(myTime); Serial.print(", ");

  pir1status = digitalRead(pir1pin); // read PIR 1 status
  pir2status = digitalRead(pir2pin); // read PIR 2 status

  // log PIR statuses to sd card and print to serial monitor
  logfile.print(pir1status); logfile.print(", ");
  logfile.print(pir2status); logfile.print(", ");
  Serial.print(pir1status); Serial.print(", ");
  Serial.print(pir2status); Serial.print(", ");  

  // visual display showing PIR 1 is active with LED
  digitalWrite(led1pin, (pir1status == HIGH ? HIGH : LOW));

  // visual display showing PIR 2 is active with LED
  digitalWrite(led2pin, (pir2status == HIGH ? HIGH : LOW));

  // initial stage both flags should be false. Waiting for either PIR 1 or 2 to be triggered
  if ((!flag12 && !flag21) && (pir1status || pir2status)) {

    // expecting pedestrian to walk from PIR 1 to 2 so turn on flag12
    if (pir1status) flag12 = true;
    // get initial time
    initialTime = millis();

    // expecting pedestrian to walk from PIR 2 to 1 so turn on flag21
    if (pir2status) flag21 = true;
    // get initial time
    initialTime = millis();

  }

  // count for direction 1 to 2
  // wait for PIR 2 to become true and then get elapsed time and add to count
  if (flag12 && !flag21 && pir2status) {
    elapsedTime = millis() - initialTime;
    if (elapsedTime > 100) count12++; // only increment counter if >0.1s between two sensors
    // set both flags to true and wait for the PIR sensors to turn off before resetting flags to false
    flag21 = true;
  }

  // count for direction 2 to 1
  // wait for PIR 1 to become true and then get elapsed time and add to count
  if (flag21 && !flag12 && pir1status) {
    elapsedTime = millis() - initialTime;
    if (elapsedTime > 100) count21++; // only increment counter if >0.1s between two sensors
    // set both flags to true and wait for the PIR sensors to turn off before resetting flags to false
    flag12 = true;
  
  }
  // flag reset if both flags have been tripped and sensors are free
  if (flag12 && flag21 && !(pir1status || pir2status)) {
    flag12 = false;
    flag21 = false;
  }
  
  // simple catch for waiting too long (>3s of only one sensor active)
  if (millis()-initialTime > 3000 && (flag12 ^ flag21)) {
    // wait for both sensors to turn off before resetting to avoid potential errors
    if (!pir2status && !pir1status) {
      flag21 = false; flag12 = false;
    }
  }

  // log data to sd card and print to serial monitor
  float speed = distance / elapsedTime;
  logfile.print(count12); logfile.print(", ");
  Serial.print(count12); Serial.print(", ");
  logfile.print(count21); logfile.print(", ");
  Serial.print(count21); Serial.print(", ");
  logfile.print(speed); logfile.print(", ");
  Serial.print(speed); Serial.print(", ");

  // create a new line for next time-step
  logfile.println(); Serial.println();

  // "flush" aka save data into sd card
  logfile.flush();
}
