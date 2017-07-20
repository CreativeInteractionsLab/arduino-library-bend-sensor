/*
 * BendSensor.cpp - library for using multiple bidirectoinal bensSensors with arduino
 * Created by Alexander Eady, July 19, 2017
 * Released to the public domain.
*/
#include "BendSensor.h"

#define CALIBRATE_ARRAY_MAX 10

BendSensor::BendSensor(){

}

BendSensor::~BendSensor(){

}

void BendSensor::initialize(int sensorPin){
  _calibrate[CALIBRATE_ARRAY_MAX];
  _pin = sensorPin;
  _threshold = 0;
  _restingVal = 512;
  _calibrateCounter = 0;

  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
    _calibrate[i] = 0;
  }  
}

void BendSensor::initialize(int sensorPin, int threshold){
  _calibrate[CALIBRATE_ARRAY_MAX];
  _pin = sensorPin;
  _threshold = threshold;
  _restingVal = 512;
  _calibrateCounter = 0;

  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
    _calibrate[i] = 0;
  }  
}

void BendSensor::calibrateMode () {
  // takes up to 10 readings from the sensors and stores them to determine restingVal of sensor in unbent state
  _calibrate[_calibrateCounter] = analogRead(_pin);
  _calibrateCounter++;
  if (_calibrateCounter >= CALIBRATE_ARRAY_MAX) {_calibrateCounter = 0;}  
}

void BendSensor::setResting () {
  // sets the resting value for the sensor using calibrateMode data
  int average = 0;
  
  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
    average += _calibrate[i];
  }
  _restingVal = average/CALIBRATE_ARRAY_MAX;

  //sets threshold, if not already defined
  if (_threshold == 0){
    int difference = 0;
    for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
      if ( abs(average - _calibrate[i]) > difference) { difference = abs(average - _calibrate[i]); }
    }

    _threshold = difference * 2;
  }
}

int BendSensor::getState (){
  // returns one of three values (0, resting; 1, bent up; -1, bent down)
  _currentVal = analogRead(_pin);
  
   if (_currentVal > _restingVal + _threshold){
    return (1);
   } else if (_currentVal < _restingVal - _threshold) {
    return (-1);
   } else {
     return (0);
   }
  
}

void BendSensor::report(){
  int repPin = _pin;
  Serial.print ("pin: ");
  Serial.print (repPin);

  int repRest = _restingVal;
  Serial.print (" , rest: ");
  Serial.print (repRest);

  int repThresh = _threshold;
  Serial.print (" , threshold: ");
  Serial.println (repThresh);
}

