#include "pca9685_rasp.h"
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <bitset>

namespace exploringRPi{


pca9685::pca9685(unsigned int i2c_bus, unsigned int i2c_address):
  I2CDevice(i2c_bus, i2c_address){
  this->i2c_bus = i2c_bus;  
  this->i2c_address = i2c_address;
  this->registers = NULL;
  this->external_clock = false;
  this->clock_frequency = INTERNAL_OSCILATOR_FREQ;
  this->wake_up();
}


void pca9685::sleep(){
  unsigned char mode1;
  mode1 = this->readRegister(PCA9685_MODE1);
  mode1 |= 1UL << MODE1_SLEEP;
  this->writeRegister(PCA9685_MODE1, mode1);
  usleep(500);
  std::cout << "a mimir -> " << (unsigned int)this->readRegister(PCA9685_MODE1) << std::endl;
}


void pca9685::wake_up(){
  unsigned char mode1;
  mode1 = this->readRegister(PCA9685_MODE1);
  mode1 &= ~(1UL << MODE1_SLEEP);
  this->writeRegister(PCA9685_MODE1, mode1);
  usleep(500);
}


/*
void pca9685::soft_reset(){
  unsigned char mode1;
  mode1 = this->readRegister(PCA9685_MODE1);
  if(mode1 & (1<<MODE1_RESTART)){
    mode1 &= ~(1UL << MODE1_SLEEP);
    this->writeRegister(PCA9685_MODE1, mode1);
    usleep(600);
    mode1 |= 1UL << MODE1_RESTART;
    this->writeRegister(PCA9685_MODE1, mode1);
  }
}
*/


void pca9685::set_output_drive(pca9685::OUTPUT_DRIVE drive){
  unsigned char mode2;
  mode2 = this->readRegister(PCA9685_MODE2);

  drive? (mode2 |= 1UL << MODE2_OUTDRV) : (mode2 &= ~(1UL << MODE2_OUTDRV));

  this->writeRegister(PCA9685_MODE2, mode2);
}// logica testada e aprovada
 // testar resultados externos


void pca9685::set_output_change(pca9685::OUTPUT_CHANGE change){
  unsigned char mode2;
  mode2 = this->readRegister(PCA9685_MODE2);
  
  change? (mode2|= 1UL << MODE2_OCH) : (mode2 &= ~(1UL << MODE2_OCH));

  this->writeRegister(PCA9685_MODE2, mode2);
}// logica testada e aprovada
 // testar resultados externos


void pca9685::set_output_inverting(bool invert){
  unsigned char mode2;
  mode2 = this->readRegister(PCA9685_MODE2);
  invert? (mode2|= 1UL << MODE2_INVRT) : (mode2 &= ~(1UL << MODE2_INVRT));
  this->writeRegister(PCA9685_MODE2, mode2);
}


void pca9685::set_pwm_frequency(float frequency){
  float prescale;
  prescale = roundf(clock_frequency/(4096*frequency)) - 1;
  this->sleep();
  this->writeRegister(PCA9685_PWM_PRESCALE, (unsigned char)prescale);
  this->wake_up();
}


void pca9685::set_pwm_duty_cycle(pca9685::CHANNEL channel, unsigned short duty_cycle){
  unsigned char* led_on_p = (unsigned char*) &duty_cycle;
  this->writeRegister(PCA9685_PWM_CH(channel), *led_on_p);
  std::cout << std::bitset<8>{*led_on_p} << std::endl;
  led_on_p++;
  this->writeRegister(PCA9685_PWM_CH(channel)+1, *led_on_p);
  std::cout << std::bitset<8>{*led_on_p} << std::endl;
}


void pca9685::disable_channel(pca9685::CHANNEL channel){
  unsigned char ledn_off_h = this->readRegister(PCA9685_PWM_CH(channel)+3) | 0b10000;
  this->writeRegister(PCA9685_PWM_CH(channel)+3, ledn_off_h);
}


void pca9685::enable_channel(pca9685::CHANNEL channel){
  unsigned char ledn_off_h = this->readRegister(PCA9685_PWM_CH(channel)+3);
  ledn_off_h &= ~(1UL << 4);
  this->writeRegister(PCA9685_PWM_CH(channel)+3, ledn_off_h);
}


} /* namespace exploringRPi */