#include <iostream>
#include <unistd.h>
#include "pca9685_rasp.h"

#define MG996R_MIN_POSITION 1*(4096*50/1000)
#define MG996R_MID_POSITION 1.5*(4096*50/1000)
#define MG996R_MAX_POSITION 2*(4096*50/1000)

using namespace exploringRPi;

int main(int argc, char *argv[]){
  /* PCA9685 servo driver setup */
  pca9685 servo_driver(1, 0x43);
  servo_driver.set_output_drive(pca9685::TOTEM_POLE);
  servo_driver.set_output_inverting(false);
  servo_driver.set_output_enable_pin(26);
  servo_driver.set_output_enable_value(LOW);
  servo_driver.set_pwm_frequency(50);

  /* Setting servo signal channels*/
  servo_driver.enable_channel(pca9685::CH00);
  servo_driver.enable_channel(pca9685::CH01);
  
  /* Making the servo attached to CH0 go to it's neutral position */
  std::cout << "Going to the neutral position" << std::endl;
  servo_driver.set_pwm_duty_cycle(pca9685::CH00, MG996R_MID_POSITION);
  sleep(5);
  
  unsigned int count = MG996R_MID_POSITION;

  /* Moving the servo slowly between it's limits */
  std::cout << "Moving between MG996R limits..." << std::endl;
  while(true){
    if(count < MG996R_MAX_POSITION){
      servo_driver.set_pwm_duty_cycle(pca9685::CH00, count);
      count ++;
      usleep(30000);
    }
    else{
      std::cout << "Returning to MIN angle" << std::endl;
      servo_driver.set_pwm_duty_cycle(pca9685::CH00, MG996R_MIN_POSITION);
      count = MG996R_MIN_POSITION;
      sleep(5);
    }
  }

  return 0;
}