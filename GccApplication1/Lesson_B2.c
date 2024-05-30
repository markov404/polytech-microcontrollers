#include <avr/io.h>
#include "lcd1602wire4.h"
#include <util/delay.h>
#include <stdio.h>

float cod, volt;
char str[12];
char n;

void ADC_ini(void) {
	ADCSRA |= (1 << ADEN);  // ��������� ���
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);  // ������� ��� = 1/8 ����. �������
	ADMUX |= (1 << REFS0);  // ������� ���������� ������� �� AVCC
}

void ADCconvert(void) {
	ADMUX &= ~(1 << MUX1) & ~(1 << MUX3) & ~(1 << MUX4) ;  // ����� ����� PA5/ADC5
	ADMUX |= (1 << MUX0) | (1 << MUX2);

	ADCSRA |= (1 << ADSC);  // ������ ���������� ��������������
	while (ADCSRA & (1 << ADSC));  // ���������, ���� �� ���������� ��������������
	cod = ADC;  // ������ � ���������� ����������� �������� ADC
}

int main(void) {
	LCD_ini();
	ADC_ini();

	setpos_to_LCD(0, 0);
	string_to_LCD("Voltage:");
	setpos_to_LCD(0, 1);
	string_to_LCD("Button:");

	while (1) {
		ADCconvert();
		volt = cod * 0.00488;

		setpos_to_LCD(9, 0);
		sprintf(str, "%.2f", volt);
		string_to_LCD(str);
		string_to_LCD("     ");

		if (volt >= 0 && volt < 0.25)
		n = 1;
		else if (volt >= 0.25 && volt < 0.5)
		n = 2;
		else if (volt >= 0.5 && volt < 0.75)
		n = 3;
		else if (volt >= 0.75 && volt <= 1)
		n = 4;
		else if (volt >= 1.05 && volt < 1.2)
		n = 5;
		else if (volt >= 1.2 && volt <= 1.5)
		n = 6;

		setpos_to_LCD(8, 1);
		sendbyte_to_LCD(n + 0x30, 1);
	}
}
//������: ���������� ������� ������� ������
//��������� ����������� �� ����� PA5/ADC5
//������������� � Proteus