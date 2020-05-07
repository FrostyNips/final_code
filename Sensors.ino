#include "Sensors.h"

void ADC_init(){
//  ADMUX = 0;
//  //ADC7 or Sensor4, left adjusted, non-freerunning mode
//  ADMUX |= (1<<REFS1)|(1<<REFS0)|(1<<ADLAR);
//  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//  ADCSRB |= (0<<MUX5);
//  DDRD |= (0<<8);
  ADMUX |= (1 << REFS0);     // Set ADC reference to AVCC
  ADMUX |= (1 << ADLAR);     // Left Adjust the result 
  ADCSRA |= (1 << ADEN);     // Enable ADC
  ADCSRA |= (1 << ADIE);     // Enable ADC Interrupt
  sei();                     // Enable Global Interrupts
  ADCSRA |= (1 << ADSC);     // Start A2D Conversions
  return;  
}
//void ADC_init1(){
//  ADMUX = 0;
//  //ADC11 or Sensor5, left adjusted, non-freerunning mode
//  ADMUX |= (1<<REFS1)|(1<<REFS0)|(1<<MUX2)|(1<<MUX1)|(1<<ADLAR);
//  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//  //ADCSRB |= (1<<MUX5);
//  
//  return;  
//}
uint8_t SensorValue(){

  //read value from ADC
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  uint8_t sensor_out = ADCH;
  
  return sensor_out;
}


  
