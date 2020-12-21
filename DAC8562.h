/*
  DAC8562.h
  
  Arduino library for Texas Instruments DAC8562 2-channel 16-bit SPI DAC
  
  External voltage reference; full-scale is 2*vref
  
  To use:
    pleae see the examples provided in this library
  
  Wiring:
    Use any digital pin for !CS (chip select).
    Data and clock use hardware SPI connections.
      For "classic" Arduinos (Uno, Duemilanove, etc.), data = pin 11, clock = pin 13
      For Teensy 2.0, data = B2 (#2), clock = B1 (#1)
      For Teensy 3.0, data = 11 (DOUT), clock = 13 (SCK)

  inspired by @machinesalem
    
  2018-07-24 @km7,  (cc) https://creativecommons.org/licenses/by/3.0/
*/

#ifndef __DAC8562_H__
#define __DAC8562_H__

#include "Arduino.h"

#ifndef USING_SOFT_SPI
  #define USING_SOFT_SPI
#endif

#define CMD_SETA_UPDATEA          0x18  // 
#define CMD_SETB_UPDATEB          0x19  // 
#define CMD_UPDATE_ALL_DACS       0x0F  // 
#define CMD_GAIN                  0x02  //
#define DATA_GAIN_B2_A2           0x0000  // 
#define DATA_GAIN_B2_A1           0x0001  // 
#define DATA_GAIN_B1_A2           0x0002  // 
#define DATA_GAIN_B1_A1           0x0003  //           

#define CMD_PWR_UP_A_B            0x20  // 
#define DATA_PWR_UP_A_B           0x0003  // Power up DAC-A and DAC-B  data

#define CMD_RESET_ALL_REG         0x28  // 
#define DATA_RESET_ALL_REG        0x0001  // 

#define CMD_LDAC_DIS              0x30  // 
#define DATA_LDAC_DIS             0x0003  // 

#define CMD_INTERNAL_REF_DIS      0x38  // Disable internal reference and reset DACs to gain = 1
#define DATA_INTERNAL_REF_DIS     0x0000  // Disable internal reference and reset DACs to gain = 1
#define CMD_INTERNAL_REF_EN       0x38  // Enable Internal Reference & reset DACs to gain = 2
#define DATA_INTERNAL_REF_EN      0x0001  // Enable Internal Reference & reset DACs to gain = 2



class DAC8562
{
  private:
    uint8_t _sck_pin;
    uint8_t _mosi_pin;
    uint8_t _miso_pin;
    uint8_t _cs_pin;
    float   _vref;
    
  public:
   
    DAC8562(uint8_t cs_pin);
    DAC8562(uint8_t cs_pin, float vref);
    DAC8562(uint8_t sck,uint8_t mosi, uint8_t miso, uint8_t cs_pin, float vref);
    void begin();
    void initialize();
    void DAC_WR_REG(uint8_t cmd_byte, uint16_t data_byte );
    void outPutValue(uint8_t cmd_byte,uint16_t input);
    void writeValue( uint8_t cmd_byte, uint8_t mid, uint8_t last);
    void writeVoltage(float input);
    void writeA(float input);
    void writeB(float input);
    uint16_t Voltage_Convert(float voltage);
};

#endif
