 unsigned int rpm;                                 //sets variable rpm
 volatile byte rpm_calib;                          //sets variable used for calibration of RPM's
 unsigned long old_time_measure;                   //sets variable old_time_measure so the code can 
                                                   //measure the time between last measurement and current one.
 void setup()                                     
 {
   Serial.begin(115200);                           //MAKE SURE YOU SET YOUR SERIAL MONITOR TO 115200 baud
   attachInterrupt(0, mf_detect, RISING);          //sets the hall sensor input pin to digital pin 2
   rpm_calib = 0;
   rpm = 0;
   old_time_measure = 0;
 }
 void loop()                                                  //Measures The RPM / frequency of sensor on states
 {
   if (rpm_calib >= 10) {                                     //if rpm_calib is greater than or equal to 20
     rpm = 30*1000/(millis() - old_time_measure)*rpm_calib*2; //Variable rpm = 30,000 / (millis() - old_time_measure) *rpm_calib * 2) 
                                                              //Last x2 makes reading more accurate or only half true RPM value is displayed
     old_time_measure = millis();                             //Set old_time_measure = millis
     rpm_calib = 0;                                           //Set rpm_calib to value of 0
     Serial.print ("RPM ");                                   //Prints "RPM "
     Serial.println(rpm,DEC);                                 //Prints the number of revolutions per minute
   }
 }
 void mf_detect()                                  //function called whenever the magnetic 
                                                   //field is detected by the arduino
 {
   rpm_calib++;                                    //Variable "rpm_calib" + 1
 // Serial.println("mf_detect");                   //Uncommenting this line prints "mf_detect" whenever the
                                                   //hall sensor detects the magnetic field which is useful for  
                                                   //counting how many revolutions happen before each measurement
                                                   //if you change the value in line 55 of this code
                                                   //in the statement "if (rpm_calib >= 10)" this statement
                                                   //is really only for calibration of the loop and changing
                                                   //the value will affect the output of "int RPM"
 }
