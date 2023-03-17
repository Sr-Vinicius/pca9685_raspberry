#include "pca9685_rasp.h"
#include <iostream>
#include <unistd.h>

namespace exploringRPi{


pca9685::pca9685(unsigned int i2c_bus, unsigned int i2c_address):
  I2CDevice(i2c_bus, i2c_address){
  this->i2c_bus = i2c_bus;  
  this->i2c_address = i2c_address;
  this->registers = NULL;
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

  drive? (mode2 |= 1UL << MODE2_OUTDRV) : (mode2 &= ~(1 << MODE2_OUTDRV));

  this->writeRegister(PCA9685_MODE2, mode2);
}// logica testada e aprovada
 // testar resultados externos


void pca9685::set_output_change(pca9685::OUTPUT_CHANGE change){
  unsigned char mode2;
  mode2 = this->readRegister(PCA9685_MODE2);
  
  change? (mode2|= 1UL << MODE2_OCH) : (mode2 &= ~(1 << MODE2_OCH));

  this->writeRegister(PCA9685_MODE2, mode2);
}// logica testada e aprovada
 // testar resultados externos


void pca9685::set_output_inverting(bool invert){
  unsigned char mode2;
  mode2 = this->readRegister(PCA9685_MODE2);
  
  invert? (mode2|= 1UL << MODE2_INVRT) : (mode2 &= ~(1 << MODE2_INVRT));

  this->writeRegister(PCA9685_MODE2, mode2);
}// logica testada e aprovada
 // testar resultados externos


// void pca9685::enable_channel(uint8_t channel){

// }

// void pca9685::disable_channel(uint8_t channel){

// }

} /* namespace exploringRPi */