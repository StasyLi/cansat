#ifndef BMP280_I2C_H_
#define BMP280_I2C_H_
#include <stdint.h>

/*��� �� ���������� ���������, �� ������ ������ ����� ����������*/
#define BMP280_DEFAULT_ADDRESS 0x77 //���� SDO ��� ���� �� ����� ���������) �� 1
#define BMP280_ALTER_ADDRESS 0x76

/*��� �� ����������� ��������� ��������� �����������
* datahsheet 3.11.2 */
#define BMP280_REGISTR_DIG_T1 0x88
#define BMP280_REGISTR_DIG_T2 0x8A
#define BMP280_REGISTR_DIG_T3 0x8C

/*��� ���������� ���������� ��� ������ � �������������� ��� ������� ��������*/
#define BMP280_REGISTR_DIG_P1 0x8E /* datasheet 3.11.2 */
#define BMP280_REGISTR_DIG_P2 0X90
#define BMP280_REGISTR_DIG_P3 0x92
#define BMP280_REGISTR_DIG_P4 0x94
#define BMP280_REGISTR_DIG_P5 0x96
#define BMP280_REGISTR_DIG_P6 0x98
#define BMP280_REGISTR_DIG_P7 0x9A
#define BMP280_REGISTR_DIG_P8 0x9C
#define BMP280_REGISTR_DIG_P9 0x9E

/* ��� ����� ����� ���������� ������ */
#define BMP280_TSB_0_5 0b000 /* datasheet 3.6.3 */
#define BMP280_TSB 62_5 0b001
#define BMP280_TSB_125 0b010
#define BMP280_TSB_250 0b011
#define BMP280_TSB_500 0b100
#define BMP280_TSB_1000 0b101
#define BMP280_TSB_2000 0b110
#define BMP280_TSB_4000 0b111

#define BMP280_REGISTR_SOFTRESET 0xE0 /* datasheet 4.3.2 table above*/

#define BMP280_REGISTR_CHIPID 0xD0
#define BMP280_CHIPID_VALUE 0x58
/*��� ��� ��� ������� �����, ����� �������� �������� id ��������� � ���������� ����
���� �������� ����������� � ����, � ���� ����*/
/* #define BMP280_REGISTER_VERSION 0xD0
* #define BMP280_REGISTER_SOFTRESET 0xE0
*/

/* ����� ��������� ��� ����������� ���������� � �������� ����������� � �������� */
#define BMP280_OVERSAMPLING_P1 0b1 /* datasheet 3.3.1 or 4.3.4 */
#define BMP280_OVERSAMPLING_P2 0b10
#define BMP280_OVERSAMPLING_P4 0b11
#define BMP280_OVERSAMPLING_P8 0b100
#define BMP280_OVERSAMPLING_P16 0b101

#define BMP280_OVERSAMPLING_T1 0b1 /* datasheet 3.3.2 */
#define BMP280_OVERSAMPLING_T2 0b10
#define BMP280_OVERSAMPLING_T4 0b11
#define BMP280_OVERSAMPLING_T8 0b100
#define BMP280_OVERSAMPLING_T16 0b101

#define BMP280_FILTER_OFF 0b00 /* datasheet 3.3.3 ����� �� �������, �� �� �������� ��������*/
#define BMP280_FILTER_COEF2 0b01
#define BMP280_FILTER_COEF4 0b10
#define BMP280_FILTER_COEF8 0b11
#define BMP280_FILTER_COEF16 0b100

#define BMP280_SPI_OFF 0x00 /* �� �����, �������� ������� � datasheet 5.3 */
#define BMP280_SPI_ON 0x01

/* ����� ���� ������� �������, ������/�� ������ �������� ��� ������������ */
#define BMP280_REGISTR_CONTROL 0xF4 /* datasheet 3.3.1 or 3.3.2 or 4.3.4 */
#define BMP280_REGISTR_STATUS 0xF3 /* datasheet 4.3.3. */
#define BMP280_REGISTR_CONFIG 0xE0
#define BMP280_REGISTR_PRESSUREDATA 0xF7 /* � datasheet 3.11.3 ��������� ��� ��, ��� ������ ����� 20 ���, � ���� ���� �������, ��� XLSB - �����-��, ������� �� ��������� �� 2 �������� ������ ����������*/
#define BMP280_REGISTR_TEMPDATA 0xFA

#define BMP280_SLEEP 0x00 /* datasheet 3.6 */
#define BMP280_FORCED 0x01
#define BMP280_NORMAL 0x11

/* �� ������, ������ �� �����, �� ������� ������ �������� (1 ������) � ��� ���� ���������. ��� mode ���� ����������*/
#define BMP280_MEAS (BMP280_OVERSAMPLING_T2 � 5) | (BMP280_OVERSAMPLING_P16 � 2) | (BMP280_FORCED)
#define BMP280_CONFIG (BMP280_TSB_250 � 5) | (BMP280_FILTER_COEF4 � 2) | (BMP280_SPI_OFF) // �� ���� ������� ��������� datasheet 4.3.5, ������ �������� �� tsb �� �� 7 ��������?
// table 3.4 helps to define the coef4
//��� �������� ��������

uint8_t BMP280_begin (uint8_t devaddr); // devaddr ����� � main.c ?
uint8_t BMP280_receiveData(int32_t *temperature, float *pressure, float *altitude);
uint8_t BMP280_read8(uint8_t address); //who is 'address' ?

#endif /* BMP280_I2C_H_ */
