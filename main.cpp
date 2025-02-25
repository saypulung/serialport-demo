/**
 * @file /example1/main.cpp
 * @author Philippe Lucidarme
 * @date December 2019
 * @brief File containing example of serial port communication
 *
 * This example send the ASCII table through the serial device
 *
 * @see https://lucidar.me
 */


// Serial library
#include "seriallib.h"
#include <unistd.h>
#include <stdio.h>
#include  <cstdint>

typedef struct {
  uint16_t number1;   // 4 bytes
  char randomPet[50]; // 50 bytes
  float randomTemp;   // 4 bytes
  char randomCity[50];// 50 bytes
  char reserved[20];  // 20 bytes
  // -----------------  128 bytes
} RandomData;

#if defined (_WIN32) || defined(_WIN64)
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyACM0"
#endif



/*!
 * \brief main  Simple example that send ASCII characters to the serial device
 * \return      0 : success
 *              <0 : an error occured
 */
int main( /*int argc, char *argv[]*/)
{
    // Serial object
    serialib serial;


    // Connection to serial port
    char errorOpening = serial.openDevice(SERIAL_PORT, 57600);


    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening!=1) {
    	printf("Error...");
    	return errorOpening;	
	}
    
	printf ("Successful connection to %s\n",SERIAL_PORT);


    // Display ASCII characters (from 32 to 128)
//    for (int c=32;c<128;c++)
//    {
//    	printf("=");
//        serial.writeChar(c);
//        usleep(10000);
//    }
//    printf("\n");
	while (1) {
		char c;
		serial.readChar(&c);
		if (c == 0x0d) {
			printf("----- reading data ---- \n");
			RandomData data;
			serial.readBytes(&data, sizeof(RandomData));
			printf("ID = %d, city = %s, pet = %s, temp = %f \n", data.number1, data.randomCity, data.randomPet, data.randomTemp);
		}
		usleep(500);
	}
    // Close the serial device
    serial.closeDevice();

    return 0 ;
}