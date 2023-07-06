#ifndef __PCA9685_RASP_H__
#define __PCA9685_RASP_H__

#include "I2CDevice.h"
#include "GPIO.h"
#include <stdint.h>

namespace exploringRPi{

/* Register addresses */
#define PCA9685_MODE1         0x00
#define PCA9685_MODE2         0x01
#define PCA9685_ALLCALL       0x05
#define PCA9685_PWM_CH0       0x06
#define PCA9685_PWM_CH(x)     (0x06 + ((x)*4))
#define PCA9685_PWM_ALL_CH    0xFA
#define PCA9685_PWM_PRESCALE  0xFE

/*MODE1 register bits*/
#define MODE1_RESTART 7
#define MODE1_EXTCLK  6
#define MODE1_AI      5
#define MODE1_SLEEP   4
#define MODE1_SUB1    3
#define MODE1_SUB2    2
#define MODE1_SUB3    1
#define MODE1_ALLCALL  0

/*MODE2 register bits*/
#define MODE2_INVRT   4
#define MODE2_OCH     3
#define MODE2_OUTDRV  2
#define MODE2_OUTNE_H 1
#define MODE2_OUTNE_L 0

#define PWM_MIN_FREQ  24
#define PWM_MAX_FREQ  1526
#define INTERNAL_OSCILATOR_FREQ 25000000
#define MAX_EXTERNAL_CLOCK_FREQ 50000000

class pca9685 : protected I2CDevice{
  public:

    enum OUTPUT_CHANGE{
      ON_STOP,
      ON_ACK
    };

    enum OUTPUT_DRIVE{
      OPEN_DRAIN,
      TOTEM_POLE
    };

    enum CHANNEL{
      CH00,
      CH01,
      CH02,
      CH03,
      CH04,
      CH05,
      CH06,
      CH07,
      CH08,
      CH09,
      CH10,
      CH11,
      CH12,
      CH13,
      CH14,
      CH15      
    };

  protected:
    unsigned int i2c_bus, i2c_address;
    unsigned char *registers;
    unsigned int clock_frequency;
    bool external_clock;
    int oe_pin;

  public:
    pca9685(unsigned int i2c_bus, unsigned int i2c_address);
    virtual ~pca9685(){}

    void sleep(void);
    void wake_up(void);
    void restart(void);
    void set_output_drive(pca9685::OUTPUT_DRIVE drive);
    void set_output_change(pca9685::OUTPUT_CHANGE change);
    void set_output_inverting(bool invert);
    void set_output_enable_value(GPIO_VALUE oe);
    void set_output_enable_pin(unsigned int pin);
    unsigned int get_output_enable_pin(void);
    void config_outne_bits(bool outne_1, bool outne_0);
    //void set_external_clock(bool extclk);
    void enable_allcall_response(void);
    void disable_allcall_response(void);
    void config_allcall_address(unsigned char allcall_address);
    void set_pwm_frequency(float frequency);

    void set_pwm_duty_cycle(pca9685::CHANNEL channel, unsigned short duty_cycle);
    void disable_channel(pca9685::CHANNEL channel);
    void enable_channel(pca9685::CHANNEL channel);
    void enable_all_channel(void); // ALL_LED_ON e ALL_LED_OFF
    void disable_all_channel(void);
    void set_all_pwm_duty_cycle(unsigned short duty_cycle);
};

}  /* namespace exploringRPi */

#endif