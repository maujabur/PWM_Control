// Arduino 1.05-r2
// Arduino Mega

#include <TimerOne.h>
#include "Interval.h"

#define DC_MIN 22 // minimum duty cycle to spin minus 2
#define DC_RUN 40 // minimum duty cycle to spin without starter
#define DC_STARTER 100 // duty cycle during starter pulse
#define ST 200 // starter pulse duration

Interval starter(10000);
Interval readPot(500);

const int fanPin = 12;

void setup(void)
{
  Timer1.initialize(40);  // 40 us = 25 kHz
  analogReference(EXTERNAL);
}
float dutyCycle = 0;
float oldDC = 0;
void loop(void)
{
  if (readPot.check()){
    dutyCycle = map(analogRead(A0), 0, 1023, DC_MIN,100);
    if (dutyCycle == DC_MIN) {
      dutyCycle =0;
    }
    if (dutyCycle != oldDC) {
      setPWM (dutyCycle);
      oldDC = dutyCycle;
    }
  }

  if (dutyCycle>DC_MIN && dutyCycle<DC_RUN && starter.check()){
    Serial.println("!");
    setPWM (DC_STARTER);
    delay(ST);
    setPWM (dutyCycle);
  }
}

inline void setPWM (float dutyCycle){
  Timer1.pwm(fanPin, (dutyCycle/(float)100) * 1023);
}

// This example creates a PWM signal with 25 kHz carrier.
//
// Arduino's analogWrite() gives you PWM output, but no control over the
// carrier frequency.  The default frequency is low, typically 490 or
// 3920 Hz.  Sometimes you may need a faster carrier frequency.
//
// The specification for 4-wire PWM fans recommends a 25 kHz frequency
// and allows 21 to 28 kHz.  The default from analogWrite() might work
// with some fans, but to follow the specification we need 25 kHz.
//
// http://www.formfactors.org/developer/specs/REV1_2_Public.pdf
//
// Connect the PWM pin to the fan's control wire (usually blue).  The
// board's ground must be connected to the fan's ground, and the fan
// needs +12 volt power from the computer or a separate power supply.






