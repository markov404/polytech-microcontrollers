/*
 * Joystick.c
 * �� ������� ��������� ���������� X � Y ���������
 *  Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>

float cod_x, cod_y;
char str[12]; // ������ ��� ������ ���������� �� �������

// ������������� ���
void ADC_ini(void)
{
    ADCSRA |= (1 << ADEN); // ��������� ���
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // ������� ��� = 1/8 ����. �������
    ADMUX |= (1 << REFS0); // ������� ���������� ������� �� AVCC
}

// ������� �������������� ���
float ADCconvert(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // ����� ������
    ADCSRA |= (1 << ADSC); // ������ ���������� ��������������
    while (ADCSRA & (1 << ADSC)); // ���������, ���� �� ���������� ��������������
    return ADC; // ������� ���������
}

void cod_to_LCD(float cod, uint8_t pos_x, uint8_t pos_y)
{
    // ����� ���� �� �������
    sprintf(str, "%.0f", cod);
    setpos_to_LCD(pos_x, pos_y);
    string_to_LCD(str); // ������� ������ � ����������� �� �������
    string_to_LCD("     "); // ������� �������, ������� ����� �������� � �������� ������ ������
}

int main(void)
{
    // ����� 0 ����� � �� ���� � ������������� ����������
    DDRA &= ~(1 << 0);
    PORTA |= (1 << 0);
    // ������������� ������� � ����������� ���
    LCD_ini();
    ADC_ini();
    // ����� �������� �� �������
    setpos_to_LCD(0, 0);
    string_to_LCD("X:");
    setpos_to_LCD(8, 0);
    string_to_LCD("Y:");
    setpos_to_LCD(0, 1);
    string_to_LCD("Button:");
    
    while (1)
    {
        // ������ � ����������� X
        cod_x = ADCconvert(2); // ����� ������� ������ ��������������
        cod_to_LCD(cod_x, 2, 0); // ��������� � ����� �� ������� ���������� X
        
        // ������ � ����������� Y
        cod_y = ADCconvert(3); // ����� �������� ������ ��������������
        cod_to_LCD(cod_y, 10, 0); // ��������� � ����� �� ������� ���������� Y
        
        // ������ � ������� ���������
        setpos_to_LCD(7, 1);
        // ���� ������ ������ - �������� pressed
        if (~PINA & (1 << 0))
            string_to_LCD("pressed    ");
        else // ���� ��� - not pressed
            string_to_LCD("not pressed");
        
        _delay_ms(500); // ��������� �������� ��� �������� ������ ������ �� �������
    }
}
//������: �������� �� ������� ����� ���������� Y ���������.
// ������������� � Proteus
