 #define F_CPU 16000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motors.h"
#include "Sensors.h"



#define THRESHOLD 100
#define THRESHOLD_redlower 35
#define THRESHOLD_redupper 50
#define THRESHOLD_purplelower 20
#define THRESHOLD_purpleupper 35
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

   sensor[1] = var[9]; //sidemarker left
   sensor[2] = var[6]; //sensor 2
   //sensor[3] = var[7]; //sensor 3
   sensor[4] = var[8]; //sensor 4
   sensor[5] = var[11]; //sensor 5
   //sensor[6] = var[]; //sensor 6
  sensor[7] = var[10]; //sensor 7
   sensor[8] = var[5]; //sidemarker right
  bool stop = false;
  
   // Going Straight
     if (sensor[4]>THRESHOLD && sensor[5]>THRESHOLD && sensor[2]<THRESHOLD && sensor[7]<THRESHOLD&& !stop) {
      
      motorSpeeds[0] = 105; // 120
      motorSpeeds[1] = 90; // 120
      if (sensor[8]>THRESHOLD){
        
        
        stop = true; 
        
        
     }     
//      if (sensor[1]>THRESHOLD_purplower && sensor[1]<THRESHOLD_purpupper) {
//      motorSpeeds[0] = 90; // 120
//      motorSpeeds[1] = 90; // 120 }
//      if (sensor[1]>THRESHOLD_redlower && sensor[1]<THRESHOLD_redupper) {
//      motorSpeeds[0] = 130; // 120
//      motorSpeeds[1] = 130; // 120
//     }
//     }
     
     }
     
     // Cross-Road
      else if (sensor[2]>THRESHOLD && sensor[4]>THRESHOLD && sensor[5]>THRESHOLD && sensor[7]>THRESHOLD && !stop) {
      motorSpeeds[0] = 130;//120
      motorSpeeds[1] = 130; //120
      }

      // Purple
//     else if (sensor[1]>THRESHOLD_purplelower && sensor[1]<THRESHOLD_purpleupper) {
//      motorSpeeds[0] = 90; // 120
//      motorSpeeds[1] = 90; // 120
//     }

    //    Red
//     else if (sensor[1]>THRESHOLD_redlower && sensor[1]<THRESHOLD_redupper) {
//      motorSpeeds[0] = 130; // 120
//      motorSpeeds[1] = 130; // 120
//     }

    
     
     //Turn Right
     else if (sensor[4]<THRESHOLD&&sensor[5]>THRESHOLD&& !stop)  {
         
            motorSpeeds[0] = 130; // 100
            motorSpeeds[1] = 10; // 40
     }
     else if (sensor[2]<THRESHOLD&&sensor[7]>THRESHOLD&& !stop)  {
       
          motorSpeeds[0] = 150; //100
          motorSpeeds[1] = 0; //0
     }


     //turn left
     else if(sensor[5]<THRESHOLD&&sensor[4]>THRESHOLD&& !stop){
       
          motorSpeeds[0] = 10; //40
          motorSpeeds[1] = 120; //100
     }
     else if (sensor[7]<THRESHOLD && sensor[2]>THRESHOLD&& !stop)  {
        
          motorSpeeds[0] = 0; //0
          motorSpeeds[1] = 150; //100
      }
      
      else if(sensor[8]>THRESHOLD && sensor[1]<THRESHOLD&& !stop){
        motorSpeeds[0] = STOP; //STOP
        motorSpeeds[1] = STOP; //STOP
      }
      else if (sensor[2]<THRESHOLD && sensor[4]<THRESHOLD && sensor[5]<THRESHOLD && sensor[7]<THRESHOLD && !stop ) {
      
        motorSpeeds[0] = STOP; //STOP
        motorSpeeds[1] = STOP; //STOP
      } 
      

      if (stop){
        
        motorSpeeds[0] = STOP; //STOP
        motorSpeeds[1] = STOP; //STOP
      }
      setMotorSpeeds(motorSpeeds);

     
     }
  return 0;
}
   
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
