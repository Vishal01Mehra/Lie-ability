#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

int moistureSensor = A0;
int moisture;
int moistureNow;
const int PulseWire = A1;
const int LED13 = 13;
int Threshold = 509;

int flag = 0;
int average = 0;
int average2 = 0;
int Finalaverage =0;


int myBPM;

PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);
  pulseSensor.analoglInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  pinMode(moistureSensor, INPUT);
//  if (pulseSensor.begin()) {
//    Serial.println("Reading Started");
//  }

}

void loop() {

  int tempMoisture = analogRead(moistureSensor);
  moisture = map(tempMoisture, 1023, 0, 0, 10000);
  
  if (moisture >= 200) {
    flag = 1;
//    Serial.println("Please keep your hand still for few seconds");
//    delay(2000);
//    Serial.println("Reading.....");
    ReadMoisture();
    ReadBPM();
    int Final = average + average2;
    Serial.println(Final);


  }
  else {
    flag = 0;
//    Serial.println("Please keep your fingers on the device to start");
  }

}

void ReadMoisture() {
  if (flag == 1) {
    for (int i = 0; i < 100; i++) {
      average = average + moisture;
    }
    average = average / 100;
//    Serial.print("Average Moisture: ");
//    Serial.println(average);
  }
  else {
//    Serial.println("Please put back your finger");


  }
}

void ReadBPM() {
  myBPM = pulseSensor.getBeatsPerMinute();
  if (flag == 1) {
    for (int i = 0; i < 10; i++) {
      average2 = average2 + myBPM;
    }
    average2 = average2 / 10;
//    Serial.print("Average BPM: ");
//    Serial.println(average2);
    Threshold = average2 - 1;
//    Serial.print("Threshold: ");
//    Serial.println(Threshold);

  }
}
