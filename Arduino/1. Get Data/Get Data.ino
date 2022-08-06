#include"DFRobot_LIDAR07.h"
#define USE_IIC
#define KNOB 0
#define echoPinUltra 2
#define trigPinUltra 3
#define piezo 4

DFROBOT_LIDAR07_IIC LIDAR07;

int knobPowerPrev = 0;
int distanceUltra;
long durationUltra;
int distanceToF;
int amplitudeToF;

void setup()
{
  pinMode(trigPinUltra, OUTPUT);
  pinMode(echoPinUltra, INPUT);
  pinMode(piezo, OUTPUT);
  uint32_t version;
  Serial.begin(115200);
  while(!LIDAR07.begin()){
    //Serial.println("Sensor Error 01");
    delay(100);
  }
  
  LIDAR07.startFilter();
}

void loop()
{
  int errinfo;
  int knobPower = map(analogRead(KNOB), 1, 1024, 1, 200);
  //Serial.println(knobPower);
  if(knobPower > 100 && knobPowerPrev <= 100){

    //tone(4,220,100);
    //US
    digitalWrite(trigPinUltra, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinUltra, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinUltra, LOW);
    
    durationUltra = pulseIn(echoPinUltra, HIGH);
    distanceUltra = durationUltra * 0.34 / 2;
    //Serial.println(durationUltra);
    //Serial.println(distanceUltra);
    //LIDAR
     while(!LIDAR07.startMeasure()){
      //delay(100);
    }
    distanceToF =  LIDAR07.getDistanceMM();
    amplitudeToF = LIDAR07.getSignalAmplitude();
   
    Serial.println((String) distanceUltra + "," + distanceToF +"," + amplitudeToF);
    
    delay(100);
  }
  else{
    //noTone(piezo);
    Serial.println("b");
    delay(100);
  }
  
}
