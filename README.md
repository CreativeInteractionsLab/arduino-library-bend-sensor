# arduino-library-bend-sensor
A library for flexpoint bend sensors for Arduino - easy to add bend sensors to your project, calibrate, get their state. Work in progress

Currently

    BendSensor();          //constructor - not using to instantiate anything, instead using initialize functions
    ~BendSensor();         //destructor
    void initialize(int sensorPin); //needs the analog pin that the sensor is connected to
    void initialize(int sensorPin, int threshold); //needs the analog pin, and threshold (amount to consider bent) to be passed to it
    void calibrateMode (); // takes up to 10 readings from the sensors and stores them to determine restingVal of sensor in unbent state
    void setResting ();    // sets the resting value for the sensor using calibrateMode data (also calculates a threshold if none has been given)
    int  getState ();      // returns one of three values (0, resting; 1, bent up; -1, bent down) 
    void report();         // prints vars to serial 
