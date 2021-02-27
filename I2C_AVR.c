#include "I2C_AVR.h"
#include <avr/io.h>
#include <util/delay.h>

//Включение шины
void I2CInit(uint16_t CPU_F, uint16_t SCL_F){
	//Включение шины
	TWBR = (((CPU_F)/(SCL_F)-16)/2);
	TWSR = 0;
	//Включение шины
	TWCR |= (1<<TWEN);
}

//Остановка работы
void I2CClose(){
	TWCR = (~(1<<TWEN));
}

//Cтарт работы
void I2CStart(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));
}

void I2CStop(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}

uint8_t I2WriteByte(uint8_t data){
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40){

		return 1;
	}else{
		return 0; //Error
	}
}

uint8_t I2ReadByte(uint8_t *data, uint8_t ack){
	if(ack){
		TWCR |= (1<<TWEA);
	}else{
		TWCR&=(~(1<<TWEA));
	}

	TWCR|=(1<<TWINT);

	while(!(TWSR & (1<<TWINT)));

	if((TWSR & 0xF8) == 0x58 || (TWSR & 0xF8) == 0x50){

	*data = TWDR;
	return 1;
	}else{
	return 0; //Error
	}
}

void I2CWriteRegister(uint8_t addr, uint8_t reg, uint8_t value){
	I2CStart(); // Cтартовые условия
	I2WriteByte(addr<<1); //Посылаем адресс устройства(1 байт)
	I2WriteByte(reg); //Посылаем адресс регистра
	I2WriteByte(value);//Посылаем значение
	_delay_ms(10);//Ждём 10 секунд
	I2CStop(); //Остановка
	_delay_ms(6);
}

void I2CReadBytes(uint8_t dev_addr, uint8_t register_addr, uint8_t num, uint8_t *buffer){

	I2CStart();
	I2WriteByte(dev_addr<<1);
	I2WriteByte(register_addr<<1);

	I2CStart();
	I2WriteByte((dev_addr<<1)+1);//Устройство передаёт данные

	for (uint8_t i = 0; i < num; i++){
		I2ReadByte(buffer,1);
		buffer++;
	}
}
