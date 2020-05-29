#define F_CPU 16000000UL


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
int count;


int button_setup()
{
  DDRC &= ~(1<<7);
  DDRC &= ~(1<<6);

  PORTC |= (1<<7);
  PORTC |= (1<<6);
}


int main()
{ 
  
  button_setup();
  //initalise peripherals
  
  timer0_init();
  
  ADC_init();
  // ADC_init1();
  
  //create variables
  uint8_t motorSpeeds[2] = {0,0};
  bool on = false;
  
  while(1)
  {
    if(PINC&(1<<7) && on == false)
    {
      on = true ;
    }
    
  while(on == true)
  {
    sensor[1] = var[10]; //sidemarker left
    sensor[2] = var[7]; //sensor 2
    sensor[4] = var[8]; //sensor 4
    sensor[5] = var[11]; //sensor 5
    sensor[7] = var[9]; //sensor 7
    sensor[8] = var[5]; //sidemarker right

         
    // Going Straight
    if (sensor[4] > THRESHOLD && sensor[5] > THRESHOLD) 
    {  
      motorSpeeds[0] = 170; // 85
      motorSpeeds[1] = 170; // 75     
    }  

    // stop on right line
    else if (sensor[1] < THRESHOLD && sensor[2] < THRESHOLD && sensor[8] > THRESHOLD && sensor[5] > THRESHOLD) 
    { 
      motorSpeeds[0] = 0; // 120
      motorSpeeds[1] = 0; // 120
      on = false;
    }

     // Turn Right
    else if (sensor[4] < THRESHOLD && sensor[5] > THRESHOLD)  
    {
       motorSpeeds[0] = 160; // 140
       motorSpeeds[1] = 15; // 10 
    
    }
    else if (sensor[2] < THRESHOLD && sensor[7] > THRESHOLD)  
    {       
       motorSpeeds[0] = 150; //100
       motorSpeeds[1] = 0; //0 
      
    }
 else if (sensor[5] > THRESHOLD && sensor[7] > THRESHOLD)  
    {       
       motorSpeeds[0] = 150; //100
       motorSpeeds[1] = 0; //0
    }

    // Turn Left
    else if(sensor[5] < THRESHOLD && sensor[4] > THRESHOLD)
    {
       motorSpeeds[0] = 15; //10
       motorSpeeds[1] = 160; //140 
     
    }
    else if (sensor[7] < THRESHOLD && sensor[2] > THRESHOLD)  
    {
       motorSpeeds[0] = 0; //0
       motorSpeeds[1] = 150; //100 
    }


    // Read White
    else if (sensor[2] < THRESHOLD && sensor[4] < THRESHOLD && sensor[5] < THRESHOLD && sensor[7] < THRESHOLD) 
    {
       motorSpeeds[0] = STOP; //STOP
       motorSpeeds[1] = STOP; //STOP
    } 


    setMotorSpeeds(motorSpeeds);


    if (PINC&(1<<6)  && on == true)
    {
      motorSpeeds[0]= STOP;
      motorSpeeds[1]= STOP;
      setMotorSpeeds(motorSpeeds);
      on = false;
      break;
      PORTC |= (1<<6);
    }
  }
 }
}


ISR(ADC_vect)           
  {
 //Count up to n channels
 //(myvar[i]) = ADCH;
 //Serial.println(i);
  if (++i >= ADC_CHANNELS)
      {i = 0;} 
      
  if (i <= 7){
     (var[i]) = ADCH;
     //ADCSRB |= (0<<MUX5);
     ADCSRB = 0b00000000;
     ADMUX = (1<<ADLAR) | (1<<REFS0) | i; //Select ADC Channel
    }
  if (i > 7){
    (var[i]) = ADCH;
     //ADCSRB |=  (1<<MUX5);
     ADCSRB = 0b00100000;
     int value = i - 7; //back to 0 1 2 3 4 
     ADMUX = (1<<ADLAR) | (1<<REFS0) | value; //Select ADC Channel
    }
  
 
  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
  }
