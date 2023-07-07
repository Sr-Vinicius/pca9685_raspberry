# A PCA9685 C++ Library for Embedded Linux 

<img src="https://img.shields.io/badge/version-v1.0-red"> <img src="https://img.shields.io/badge/license-LGPL 2.1-red">

C++ library for the multi-channel PWM generator PCA9685. Originally designed to be an I²C-bus LED controller IC, but it's also used to control servos.

## Supported Features
* Independent PWM signal generation on all 16 channels;
* Multiple PCA9685 programming simultaneously with the ALLCALL address (configurable);
* PWM signal frequency configuration;
* PCA9685 sleep function;
* PCA9685 restart function;
* Generating the same PWM signal on all channels via *all_channel* methods;
* Full device configuration including: pin topology, pin inverting, output change;

## Building and executing the test code
Clone the repository to your Linux device:
```bash
git clone https://github.com/Sr-Vinicius/pca9685_raspberry.git
```

Go to the examples folder:
```bash
cd pca9685_raspberry/examples/i2c_test
```

And then, just run the make command:
```bash
make
```

Finally, run the test:
```bash
./i2c_test
```

# Next features

* Enable external clock source to the PCA9685;

By now, the chip can only work with it's internal oscilator clock source. It's possible to supply external clock to the PCA9685, configuring the appropriate registers and generating a clock signal with the Linux device or with dedicated hardware.

## License
This library is licensed under the **GNU LGPL v2.1**. 

## Acknowledgements
This library is based on the C++ I2C device template developed by [Derek Molloy](https://github.com/derekmolloy), and available [here](https://github.com/derekmolloy/exploringrpi).