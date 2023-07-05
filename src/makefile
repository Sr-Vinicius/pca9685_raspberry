objects = i2c_test.o pca9685_rasp.o I2CDevice.o GPIO.o

i2c_test : $(objects)
	g++ -o i2c_test  $(objects) -pthread

i2c_test.o : i2c_test.cpp pca9685_rasp.h I2CDevice.h GPIO.h
	g++ -c i2c_test.cpp

pca9685_rasp.o : pca9685_rasp.cpp I2CDevice.h GPIO.h
	g++ -c pca9685_rasp.cpp

I2CDevice.o : I2CDevice.cpp
	g++ -c I2CDevice.cpp

GPIO.o : GPIO.cpp
	g++ -c GPIO.cpp

.PHONY : clean
clean :
	rm i2c_test $(objects)
