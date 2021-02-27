#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include "uart.h"
#include "i2c_avr.h"
#include "bmp280_i2c.h"

if (c == '\n') {
	USART_PutChar('\r', stream);
	USART_SendByte(c);
	return 0;
}

int main() {
	int32_t temperat;
	float pressure, altitude;
	float zero = 0;

	USART_Init(9600);
	I2CInit(F_CPU, 100000);

	stdout = &mystdout; //что это значит?
	printf("\nBMP280 I2C Demo\n");
	bmp280_connection = BMP280_begin(BMP280_DEFAULT_ADDRESS);
	if (bmp280_connection == 1) {
		printf("BMP280 CONNECTION SUCCEEDED!\n");
	} else {
		printf("BMP280 CONNECTION FAILED :( \n");
		return 0;
	}

	for (int i=0; i<10; i++) {
		BMP280_receiveData(&temperature, &pressure, &altitude);
		zero += altitude;
	}
	zero/=10;
	while (1) {
		bmp280_data_received = BMP280_receiveData(&temperature, &pressure, &altitude);
		if (bmp280_data_received == 1) {
			printf ("temp = %ld\n press = %.4f\n alt = %.4f\n", temperature, pressure, altitude - zero);
		} else {
			printf ("BMP280 measurment failed");
		}
	int chid = BMP280_read8(BMP280_REGISTR_CHIPID);
	printf("chID = %.2X\n", chid);
	_delay_ms(200); //почему именно такой?
}

}

