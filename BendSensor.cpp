/*
 * BendSensor.cpp - library for using multiple bidirectoinal bensSensors with arduino
 * Created by Alexander Eady, July 19, 2017
 * Released to the public domain.
*/
#include "BendSensor.h"

#define CALIBRATE_ARRAY_MAX 10
#define SENSOR_MODE 512

BendSensor::BendSensor(){

}

BendSensor::~BendSensor(){

}

void BendSensor::initialize(int sensorPin){
  this->_calibrate[CALIBRATE_ARRAY_MAX];
  this->_pin = sensorPin;
  this->_threshold = 0;
  this->_restingVal = SENSOR_MODE;
  this->_calibrateCounter = 0;
  this->_calibrated = false;

  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
    this->_calibrate[i] = SENSOR_MODE;
  }  
}

void BendSensor::initialize(int sensorPin, int threshold){
  this->_calibrate[CALIBRATE_ARRAY_MAX];
  this->_pin = sensorPin;
  this->_threshold = threshold;
  this->_restingVal = SENSOR_MODE;
  this->_calibrateCounter = 0;
  this->_calibrated = false;

  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
    this->_calibrate[i] = SENSOR_MODE;
  }  
}

void BendSensor::calibrateMode () {
  // takes up to 10 readings from the sensors and stores them to determine restingVal of sensor in unbent state
	if (this->_calibrated == false){

		int counter = 0;

		for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){

			if (counter <= CALIBRATE_ARRAY_MAX) {

				Serial.print ("counter: ");
				Serial.print (counter);
				Serial.print (", reading: ");
				Serial.print (analogRead(_pin));

				this->_calibrate[counter] = analogRead(_pin);

				Serial.print ("stored: ");
				Serial.println (this->_calibrate[counter]);

		  		counter++;		  		
			}	  
		  	
		  	delay (100);
	  	}

	  	// sets the resting value for the sensor using calibrateMode data
		  int average = 0;
		  
		  for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
		    average += this->_calibrate[i];
		  }

		  average = average/CALIBRATE_ARRAY_MAX;
		  this->_restingVal = average;

		  Serial.print ("average: ");
		  Serial.print (average);
		  Serial.print (", stored: ");
		  Serial.println (this->_restingVal);

		  //sets threshold, if not already defined
		  int difference = 0;
		  if (this->_threshold == 0){
		    
		    for (int i = 0; i < CALIBRATE_ARRAY_MAX; i++){
		      if ( abs(average - this->_calibrate[i]) > difference) { difference = abs(average - this->_calibrate[i]); }
		    }

		    this->_threshold = difference * 20;
		  }

		  Serial.print ("threshold: ");
		  Serial.print (difference * 20);
		  Serial.print (", stored: ");
		  Serial.println (this->_threshold);

	  	this->_calibrated = true;
	}
  	 
}

void BendSensor::reset () {
  // sets the resting value for the sensor using calibrateMode data
  this->_calibrated = false;
  
}

int BendSensor::getState (){
  // returns one of three values (0, resting; 1, bent up; -1, bent down)
  
  if (this->_calibrated == true) {
	  this->_currentVal = analogRead(_pin);
	  
	   if (this->_currentVal > this->_restingVal + this->_threshold){
	    return (1);
	   } else if (this->_currentVal < this->_restingVal - this->_threshold) {
	    return (-1);
	   } else {
	     return (0);
	   }
	}
	else {
		return (0);
	}  
}

void BendSensor::report(){
  int repPin = this->_pin;
  Serial.print ("pin: ");
  Serial.print (repPin);

  int repRest = this->_restingVal;
  Serial.print (" , rest: ");
  Serial.print (repRest);

  int repThresh = this->_threshold;
  Serial.print (" , threshold: ");
  Serial.println (repThresh);
}


