#include <SD.h>

// initializing LED indicating PIR 1
// initializing LED indicating PIR 2

// Digital Pin
// Digital Pin
// SETTING THE STATUS OF PIR #1 TO A BOOLEAN DATA TYPE
// SETTING THE STATUS OF PIR #2 TO A BOOLEAN DATA TYPE

// This is your distance in meters (ft. * 0.3)

// count for walking from PIR 1 to PIR 2
// count for walking from PIR 2 to PIR 1

// check if walking from 1 to 2 has been triggered
// check if walking from 2 to 1 has been triggered
unsigned long initialTime = 0; // initial time of current walking pass
float totalTime = 0; // holds time difference between current time and total time
float checkTime = 0; // holds time difference between current time and total time (used as a check to avoid overwritting totalTime)

const int chipSelect = 10; // initializing chip

File logfile; // the logging file

void setup() {
  // setup serial terminal
  Serial.begin(115200);

  // initialize PIR and LED

  // delay(10000); // PIR needs to warm up. Wait at least 10 seconds before starting

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
  /*
  unsigned long myTime = millis(); // Get current time

  // log current time-step to sd card and print to serial monitor


  // read PIR 1 status
  // read PIR 2 status

  // log PIR statuses to sd card and print to serial monitor

  // visual display showing PIR 1 is active with LED


  // visual display showing PIR 2 is active with LED


  // initial stage both flags should be false. Waiting for either PIR 1 or 2 to be triggered
  if (((flag12 == false) && (flag21 == false)) && ((pir1Status == true) || (pir2Status == true))) {

    // expecting pedestrian to walk from PIR 1 to 2 so turn on flag12
    // get initial time


    // expecting pedestrian to walk from PIR 2 to 1 so turn on flag21
    // get initial time



  }

  // count for direction 1 to 2
  // wait for PIR 2 to become true and then get elapsed time and add to count


    // set both flags to true and wait for the PIR sensors to turn off before resetting flags to false

    
  

  // count for direction 2 to 1
  // wait for PIR 1 to become true and then get elapsed time and add to count


    // set both flags to true and wait for the PIR sensors to turn off before resetting flags to false

    


  // flag reset


  
  // simple catch for waiting too long
  // wait for both sensors to turn off before resetting to avoid potential errors


  // log data to sd card and print to serial monitor



  // create a new line for next time-step


  // "flush" aka save data into sd card

  */
}
