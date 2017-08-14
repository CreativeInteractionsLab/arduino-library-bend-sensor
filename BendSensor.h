/*
 * BendSensor.h - library for using multiple bidirectoinal bensSensors with arduino
 * Created by Alexander Eady, July 19, 2017
 * Released to the public domain.
*/
#ifndef BendSensor_h
#define BendSensor_h

#include <Arduino.h>

class BendSensor{
  public:
    BendSensor();          //constructor
    ~BendSensor();         //destructor
    void initialize(int sensorPin); //real constructor, needs the analog pin
    void initialize(int sensorPin, int threshold); //real constructor, needs the analog pin, and threshold (amount to consider bent) to be passed to it
    void calibrateMode (); // takes up to 10 readings from the sensors and stores them to determine restingVal of sensor in unbent state
    void reset();		   // sets _calibrated = false, so that the sensors will calibrate again
    int  getState ();      // returns one of three values (0, resting; 1, bent up; -1, bent down) 
    void report();         // prints vars to serial 
    
  protected:
  private:
    int _pin;              // stores the pin of the sensor
    int _threshold;        // stores the threshold value
    int _calibrate[];      // array to hold readings during calibration
    int _calibrateCounter; // counter, determines where in the _calibrate array we store values, loops when full.
    int _restingVal;       // holds the resting (unbent) value of the sensor
    int _currentVal;       // most recent reading from the sensor
    int _previousVal;      // previous reading, for state changes
    bool _calibrated;	   //if the sensor is not calibrated, will always return neutral
};
#endif
