objects = i2c_test.o pca9685_rasp.o I2CDevice.o GPIO.o

headers := ../../inc
source := ../../src

vpath %.h $(headers)
vpath %.cpp $(source)

i2c_test : $(objects)
	g++ -I $(headers) -I $(source) -o i2c_test  $(objects) -pthread

i2c_test.o : i2c_test.cpp pca9685_rasp.h I2CDevice.h GPIO.h
	g++ -I $(headers) -I $(source) -c i2c_test.cpp

pca9685_rasp.o : pca9685_rasp.cpp I2CDevice.h GPIO.h
	g++ -I $(headers) -I $(source) -c $(source)/pca9685_rasp.cpp

I2CDevice.o : I2CDevice.cpp
	g++ -I $(headers) -I $(source) -c $(source)/I2CDevice.cpp

GPIO.o : GPIO.cpp
	g++ -I $(headers) -I $(source) -c $(source)/GPIO.cpp

.PHONY : clean
clean :
	rm i2c_test *.o
