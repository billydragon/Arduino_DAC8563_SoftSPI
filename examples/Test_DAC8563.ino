#include "DAC8562.h"


#define REF_POWER 3.3383

#define USING_SOFT_SPI

#ifdef USING_SOFT_SPI
#define MOSI    4
#define MISO    5
#define SCK     6
#endif

//CLR and LDAC = GND
//Arduino Leonardo (SCLK,DIN,CS) = SCK,MOSI,10
//Arduino UNO (SCLK,DIN,CS) = 13,11,10


#define SS  10    //PIN SYNC on DAC8563 Board
#define DAC_MIN   512 
#define DAC_MAX   65024

            //DAC8562( uint8_t sck,uint8_t mosi, uint8_t miso, uint8_t cs_pin, float vref)
DAC8562 dac=DAC8562(SCK,MOSI,MISO,SS,REF_POWER);

void setup() {
  dac.begin();
  Serial.begin(115200);
  delay(200);  
Serial.println("Enter value: (-255:255).");
}

void Set_DAC_A(int16_t val)
{
  dac.outPutValue(CMD_SETA_UPDATEA,val);
  
}

void Set_DAC_B(int16_t val)
{
  dac.outPutValue(CMD_SETB_UPDATEB,val);
  
}


void loop() {
  char buff[64];
  // put your main code here, to run repeatedly:
volatile int force =0;
volatile int DACValue=0;
volatile float DACVoltage =0;
  while(Serial.available()>0)
    {
      Serial.setTimeout(100);
      force = Serial.parseInt();
       DACValue = map(force,-255,255,DAC_MAX,DAC_MIN);       
        
      sprintf(buff,"force = %d, DACValue = %d", force,DACValue);
      Serial.println(buff);
        
     Set_DAC_A(DACValue);
     Set_DAC_B(-DACValue);
    
      //dac.writeA(DACVoltage);
      //dac.writeB(DACVoltage);
      
    }
  
  
}
