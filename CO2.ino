/************************Hardware Related Macros*********|***************************/
#define         MG_PIN                       (0)     //define which analog input channel you are going to use
#define         ADJ_PIN                      (1)     //define which pin is connected to potentiometer for input trim
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier

/***********************Software Related Macros************************************/
#define         READ_SAMPLE_TIMES            (10)     //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_INTERVAL         (50)     //define the time interval(in milisecond) between each samples in normal operation

/**********************Application Related Macros**********************************/
//These values differ from sensor to sensor. User should derermine this value.
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         MAX_POINT_VOLTAGE            (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define         ZERO_POINT_X                 (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define         REACTION_VOLTGAE             (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

/*****************************Globals***********************************************/
float           CO2Curve[3]  =  {ZERO_POINT_X, ZERO_POINT_VOLTAGE, (REACTION_VOLTGAE / (2.602 - 4))};
//Two points are taken from the curve.With these two points, a line is formed which is
//"approximately equivalent" to the original curve. You could use other methods to get more accurate slope

//CO2 Curve format:{ x, y, slope};point1: (lg400=2.602, 0.324), point2: (lg10000=4, 0.265)
//slope = (y1-y2)(i.e.reaction voltage)/ x1-x2 = (0.324-0.265)/(log400 - log10000)

int getCO2() {
  float mg = readAnalogVolatge(MG_PIN);
  float adj = readAnalogVolatge(ADJ_PIN);
#ifdef DEBUG
  Serial.println("Adjustment voltage: " + String(adj));
  Serial.println("CO2 voltage: " + String(mg));
  Serial.println("MG811 voltage: " + String(mg/DC_GAIN));
#endif
  mg -= adj;
  return MGGetPercentage(mg, CO2Curve);
}

static float readAnalogVolatge(int pin) {
  int i;
  float v = 0;
  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    v += analogRead(pin);
    delay(READ_SAMPLE_INTERVAL);
  }
  v = (v / READ_SAMPLE_TIMES) * 5 / 1024 ;
  return v;
}

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.
************************************************************************************/
static int  MGGetPercentage(float volts, float *pcurve) {
  volts = volts / DC_GAIN;
  int ppm = pow(10, (volts - pcurve[1]) / pcurve[2] + pcurve[0]);
  return (ppm > 350 && ppm < 10000) ? ppm : -1;
}
