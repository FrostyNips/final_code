#define F_CPU 16000000UL

#include <QTRSensors.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motors.h"
#include "Sensors.h"


#define THRESHOLD 100
#define FULL_SPEED 256
#define STOP 0
#define HALF_SPEED FULL_SPEED/2


int i;
const int ADC_CHANNELS = 13;
int var[ADC_CHANNELS];
int sensor[8];

int main()
{
  
  //initalise peripherals
  timer0_init();
  
  ADC_init();
 // ADC_init1();
  
  

  //create variables
  uint8_t motorSpeeds[2] = {0,0};
  

  
  while(1){

   //sensor[1] = var[8] //sensor 4
   sensor[2] = var[6]; //sensor 4
   sensor[3] = var[7]; //sensor 4
   sensor[4] = var[8]; //sensor 4
   sensor[5] = var[11]; //sensor 4
   sensor[6] = var[10]; //sensor 4
   sensor[7] = var[9]; //sensor 4
   //sensor[8] = var[] //sensor 4


   // Going Straight
     if (sensor[4]>THRESHOLD && sensor[5]>THRESHOLD && sensor[3]<THRESHOLD && sensor[6]<THRESHOLD ) {
      motorSpeeds[0] = 120; // 50
      motorSpeeds[1] = 120; // 50
     }
     
     //Turn Right
     else if (sensor[4]<THRESHOLD&&sensor[5]>THRESHOLD||sensor[6]>THRESHOLD)  {
         
            motorSpeeds[0] = 120; // 40
            motorSpeeds[1] = 40; // 25
     }
     else if (sensor[4]<THRESHOLD && sensor[5]<THRESHOLD && sensor[7]>THRESHOLD||sensor[6]>THRESHOLD)  {
       
          motorSpeeds[0] = 120; //50
          motorSpeeds[1] = 0; // 20
     }

     //turn left
     else if(sensor[5]<THRESHOLD&&sensor[4]>THRESHOLD||sensor[3]>THRESHOLD){
       
          motorSpeeds[0] = 40;
          motorSpeeds[1] = 120;
     }
     else if (sensor[5]<THRESHOLD && sensor[4]<THRESHOLD && sensor[2]>THRESHOLD||sensor[3]>THRESHOLD)  {
        
          motorSpeeds[0] = 0;
          motorSpeeds[1] = 120;
      }

      else if (sensor[3]<THRESHOLD && sensor[4]<THRESHOLD && sensor[5]<THRESHOLD && sensor[6]<THRESHOLD && sensor[7]<THRESHOLD && sensor[2]<THRESHOLD) {
      
      motorSpeeds[0] = STOP;
      motorSpeeds[1] = STOP;
      }
      setMotorSpeeds(motorSpeeds);
      
    
  }return 0;
}




//ISR(ADC_vect)           
//  {
// //Count up to n channels
// (var[i]) = ADCH;
// 
//  if (++i >= ADC_CHANNELS)
//      {i=0;} 
//
//  ADMUX = (1<<ADLAR) | (1<<REFS1)|(1<<REFS0)|i; //Select ADC Channel
//  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
//  //ADCSRB |= (1<<MUX5);
//  } 
   
ISR(ADC_vect)           
  {
 //Count up to n channels
 //(myvar[i]) = ADCH;
 //Serial.println(i);
  if (++i >= ADC_CHANNELS)
      {i=0;} 
      
  if (i <=7){
     (var[i]) = ADCH;
     //ADCSRB |= (0<<MUX5);
     ADCSRB = 0b00000000;
     ADMUX = (1<<ADLAR) | (1<<REFS0) | i; //Select ADC Channel
    }
  if (i>7){
    (var[i]) = ADCH;
     //ADCSRB |=  (1<<MUX5);
     ADCSRB = 0b00100000;
     int value = i - 7; //back to 0 1 2 3 4 
     ADMUX = (1<<ADLAR) | (1<<REFS0) | value; //Select ADC Channel
    }
  
 
  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
  } 




 
