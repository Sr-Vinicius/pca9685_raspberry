#include <iostream>
#include <unistd.h>
#include "pca9685_rasp.h"

using namespace exploringRPi;

int main(int argc, char *argv[]){
  std::cout << "\n===================================================" << std::endl;
  std::cout << "PCA9685 I2C test:\n\n" << std::endl;

  pca9685 pwm_driver(1, 0x43); /*bus 1, address 0x43*/

  pwm_driver.set_output_drive(pca9685::TOTEM_POLE); /*or OPEN_DRAIN, as you need*/
  pwm_driver.set_output_inverting(false);
  pwm_driver.set_output_enable_pin(26);
  pwm_driver.set_output_enable_value(LOW);
  pwm_driver.set_pwm_frequency(50);

  pwm_driver.enable_channel(pca9685::CH00);
  pwm_driver.set_pwm_duty_cycle(pca9685::CH00, 1000);

  std::cout << "Test complete!" << std::endl;
  std::cout << "Verify modified registers with the comand:\n"
               "$ i2cget -y 1 0x43 <register_addr>\n\n"
               "Here is a list of the modified registers:\n"
               "MODE1: 0x00\nMODE2: 0x01\nPRE_SCALE: 0xFE\n"
               "LED0_ON_L: 0x06\nLED_ON_H: 0x07\n"
               "LED0_OFF_L: 0x08\nLED_OFF_H: 0x09\n\n"
               "You can also check the PWM outputs using"
               "an osciloscope, a logic analizer or a LED."<<std::endl;
  return 0;
}
