#include <Arduino.h>
#include "RTC.h"

void periodicCallback();

volatile bool irqFlag = false;

volatile bool ledState = false;

RTCTime ALARM_TIME_1;
RTCTime ALARM_TIME_2;

bool Alarm1Set = true;




const int led = LED_BUILTIN;
bool isHigh = LOW;

void alarmTrigger(){

  AlarmMatch match;
match.addMatchHour();
//AlarmMatch match2;
//match2.addMatchHour();
//match2.addMatchSecond();
//AlarmMatch match2;
//match2.addMatchHour();
//match2.addMatchSecond();

  digitalWrite(LED_BUILTIN, isHigh);
  digitalWrite(13, isHigh);
  isHigh = !isHigh;

  Alarm1Set = !Alarm1Set;
  if(Alarm1Set){
    RTC.setAlarmCallback(alarmTrigger, ALARM_TIME_1, match);
  }
  else{
    RTC.setAlarmCallback(alarmTrigger, ALARM_TIME_2, match);
  }
}


void setup() {

  ALARM_TIME_1.setHour(6);
  //ALARM_TIME_1.setHour(18);
  //ALARM_TIME_1.setSecond(10);
  ALARM_TIME_2.setHour(18);

  Serial.begin(9600);


  // Initialize the RTC

  RTC.begin();


  // RTC.setTime() must be called for RTC.setPeriodicCallback to work, but it doesn't matter

  // what date and time it's set to

  RTCTime mytime(12, Month::NOVEMBER, 2025, 19, 43, 00, DayOfWeek::WEDNESDAY, SaveLight::SAVING_TIME_ACTIVE);

  RTC.setTime(mytime);

  AlarmMatch match;
match.addMatchHour();


  if (!RTC.setAlarmCallback(alarmTrigger, ALARM_TIME_1, match)) {
    Serial.println("ERROR: Initial alarm callback not set");
  }

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(13, LOW);

  alarmTrigger();
  

}


void loop(){

}
