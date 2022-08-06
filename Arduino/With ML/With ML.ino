#include"DFRobot_LIDAR07.h"
#include "model.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

#define USE_IIC

//Analog
#define KNOB 0

//Digital
#define echoPinUltra 2
#define trigPinUltra 3
#define piezo 4
#define gps_TXpin 6
#define gps_RXpin 5
#define lampu 7

DFROBOT_LIDAR07_IIC LIDAR07;
TinyGPSPlus gps;

SoftwareSerial gpsSerial(gps_RXpin, gps_TXpin);

Eloquent::ML::Port::SVM classifier;

int knobPowerPrev = 0;
int distanceUltra;
long durationUltra;
int distanceToF;
int amplitudeToF;
int prefDistTof = 0;
int diffTof = 0;
int baudRate = 9600;
int pred = 0;
float datarun[3] = {0,0,0};
String prediksi;
int channel_id = 1777919;
String writeKey = "5K23ZTWMLBDGBI2I";
double latitude = -6.885045524;
double longitude = 112.0469459245;
String str;

void setup() {
  pinMode(trigPinUltra, OUTPUT);
  pinMode(echoPinUltra, INPUT);
  pinMode(piezo, OUTPUT);
  pinMode(lampu, OUTPUT);
  
  uint32_t version;
  
  Serial.begin(9600);
  gpsSerial.begin(baudRate);
  
  while(!LIDAR07.begin()){
    delay(100);
  }
  LIDAR07.startFilter();
}

void loop() {
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
    //LIDAR
     while(!LIDAR07.startMeasure()){
      delay(100);
    }
    distanceToF =  LIDAR07.getDistanceMM();
    //amplitudeToF = LIDAR07.getSignalAmplitude();

    if(prefDistTof == 0){
      prefDistTof = distanceToF;
    }
    diffTof = distanceToF - prefDistTof;
    dataDisplay();
    //Serial.println("jalan");
    prefDistTof = distanceToF;
  }
  else{
    noTone(piezo);
    digitalWrite(lampu, LOW);
    Serial.println(F("b"));
    Serial.flush();
    delay(100);
  }
}
void dataDisplay(){
    gpsSerial.listen();
    float datarun[3] = {(float) prefDistTof, (float) distanceToF,(float) diffTof};
    prediksi = classifier.predictLabel(datarun);
    while (gpsSerial.available() > 0){
      //Serial.write(gpsSerial.read());
      if (gps.encode(gpsSerial.read())){
        if (gps.location.isValid()){
          if(prediksi == "Jalan Berlubang"){
              tone(piezo,320,500);
              digitalWrite(lampu, HIGH);
              Serial.print(datarun[0]);
              Serial.print(F(","));
              Serial.print(datarun[1]);
              Serial.print(F(","));
              Serial.print(datarun[2]);
              Serial.print(F(","));
              Serial.print(gps.location.lat(), 6);
              Serial.print(",");
              Serial.print(gps.location.lng(), 6);
              Serial.print(",");
              Serial.println(1);
            }
            else{
            Serial.print(datarun[0]);
            Serial.print(F(","));
            Serial.print(datarun[1]);
            Serial.print(F(","));
            Serial.print(datarun[2]);
            Serial.print(F(","));
            Serial.print(gps.location.lat(), 6);
            Serial.print(",");
            Serial.print(gps.location.lng(), 6);
            Serial.print(",");
            Serial.println(0);
            noTone(piezo);
            digitalWrite(lampu, LOW);
            //Serial.println("0");
          }
        }
        else
        {
          if(prediksi == "Jalan Berlubang"){
              tone(piezo,320,500);
              digitalWrite(lampu, HIGH);
              Serial.print(datarun[0]);
              Serial.print(F(","));
              Serial.print(datarun[1]);
              Serial.print(F(","));
              Serial.print(datarun[2]);
              Serial.print(F(","));
              Serial.print("0");
              Serial.print(",");
              Serial.print("0");
              Serial.print(",");
              Serial.println(1);
            }
            else{
            Serial.print(datarun[0]);
            Serial.print(F(","));
            Serial.print(datarun[1]);
            Serial.print(F(","));
            Serial.print(datarun[2]);
            Serial.print(F(","));
            Serial.print("0");
            Serial.print(",");
            Serial.print("0");
            Serial.print(",");
            Serial.println(0);
            noTone(piezo);
            digitalWrite(lampu, LOW);
            //Serial.println("0");
          }
        }
      }
    }
    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println("GPS module ga kedetect");
      delay(1000);
    }
}
void displayInfo()
{
    Serial.flush();
  delay(100);
}
