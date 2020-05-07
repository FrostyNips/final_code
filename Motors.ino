#include "Motors.h"

void timer0_init(){

  //setup PWMs, 256 prescaler, fast PWM, set on TOP, clear on compare match
  DDRB |= (1<<7);
  DDRD |= (1<<0);
  TCCR0A |= (1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00);
  OCR0A = 255;
  OCR0B = 255;
  TCCR0B |= (1<<CS02);
  
  return;
}

void setMotorSpeeds(uint8_t MotorSpeeds[]){

  //vary PWM output to change motor speeds
  OCR0A = MotorSpeeds[0];
  OCR0B = MotorSpeeds[1];

  return;
}
  
