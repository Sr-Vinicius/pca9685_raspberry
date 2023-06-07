#include <iostream>
#include <unistd.h>
#include "pca9685_rasp.h"

using namespace exploringRPi;

int main(int argc, char *argv[]){
  std::cout << "\n===================================================" << std::endl;
  std::cout << "TESTE DE TEMPLATE I2C para PCA9685\n\n" << std::endl;

  pca9685 servo_driver(1, 0x40);
  
  servo_driver.set_output_drive(pca9685::OPEN_DRAIN);
  servo_driver.set_output_drive(pca9685::TOTEM_POLE);
  servo_driver.set_output_inverting(false);

  servo_driver.set_pwm_frequency(50);

  /*
  servo_driver.enable_channel(pca9685::CH00);
  servo_driver.set_pwm_duty_cycle(pca9685::CH00, 1000);

  servo_driver.set_output_enable_pin(26); 
  servo_driver.set_output_enable_value(HIGH);
  */

  servo_driver.enable_all_channel();
  servo_driver.set_all_pwm_duty_cycle(1200);

  /*
  std::cout << "output chaange trigger test:" << std::endl;
  servo_driver.set_output_change(pca9685::ON_ACK);
  servo_driver.set_output_change(pca9685::ON_STOP);

  std::cout << "inverted logic output test:" << std::endl;
  servo_driver.set_output_inverting(true);
  servo_driver.set_output_inverting(false);
  */

  /*
  I2CDevice pca(1, 0x40);
  pca.open();
  
  std::cout << "R test - PWM freq register: " << (unsigned int)pca.readRegister(0xfe) << std::endl;
  
  std::cout << "W test - MODE1 register config: " << (unsigned int)pca.readRegister(0x00) << std::endl;
  pca.writeRegister(PCA9685_MODE1, 0x21);
  std::cout << "W test - MODE1 after config: " << (unsigned int)pca.readRegister(0x00) << std::endl;

  std::cout << "FIM DO TESTE\n" << std::endl;
  return 0;
  */
}
