#ifndef I2_CAVR_H_
#define I2_CAVR_H_

#define TRUE 1
#define FALSE 0
#include<stdint.h>

//èíèöèàëèçàöèÿ øèíû
void I2CInit(uint16_t CPU_F, uint16_t SCL_F);//ïåðåäà¸ì ÷àñòîòó

//Çàêðûòèå øèíû
void I2CClose();

//Óñëîâèÿ íà÷àëà è êîíöà ðàáîòû ïðîöåññîðà
void I2CStart();
void I2CStop();

//Ïîñëàíèå è ÷òåíèå áàéòà
uint8_t I2WriteByte(uint8_t data);
uint8_t I2ReadByte(uint8_t *data, uint8_t ack);

void I2CWriteRegister(uint8_t addr, uint8_t reg, uint8_t value);
void I2CReadBytes(uint8_t dev_addr, uint8_t register_addr, uint8_t num, uint8_t*buffer);

#endif /* I2CAVR_H_ */
