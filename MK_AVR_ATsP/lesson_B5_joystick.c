/*
 * Joystick.c
 * �� ������� ��������� ���������� X ���������
 *  Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
float cod;
char str[12];//������ ��� ������ ���������� �� �������
//������������� ���
void ADC_ini(void)
{
	ADCSRA|=(1<<ADEN);//��������� ���
	ADCSRA|=(1<<ADPS1)|(1<<ADPS0);//������� ��� = 1/8 ����. �������
	ADMUX|=(1<<REFS0);//������� ���������� ������� �� AVCC;
	
}
//������� �������������� ���
void ADCconvert(void)
{
	ADCSRA|=(1<<ADSC);//������ ���������� ��������������
	while(ADCSRA&(1<<ADSC));//���������, ���� �� ���������� ��������������
	cod=ADC;//������ � ���������� ���������� �������� ADC
}

void cod_to_LCD(void)
{
//����� ���� �� �������
		sprintf(str,"%.0f",cod);
		string_to_LCD(str);//������� ������ � ����������� �� �������
		string_to_LCD("     ");//������� �������,
		//������� ����� ��������� �������� ������ ������	
}

//
int main(void)
{
	//����� 0 ����� � �� ���� � ������������� ����������
	DDRA&=~(1<<0);
	PORTA|=(1<<0);
	//������������� ������� � ����������� ���
	LCD_ini();
	ADC_ini();
	//����� �������� �� �������
	setpos_to_LCD(0,0);
	string_to_LCD("X:");
	setpos_to_LCD(8,0);
	string_to_LCD("Y:");
	setpos_to_LCD(0,1);
	string_to_LCD("Button:");
	//
	while (1)
	{
	//..........������ � �����.X................
		//����� ������� ������ �������������� 
		ADMUX|=(1<<MUX1);
		ADMUX&=~(1<<MUX0)&~(1<<MUX2)&~(1<<MUX3);
		//��������� � ����� �� �������
		ADCconvert();
		setpos_to_LCD(2,0);
		cod_to_LCD();		
	//..........������ �  �����.Y.................
		
	//.........������ � ������� ���������.........
		setpos_to_LCD(7,1);
		//���� ������ ������ - �������� pressed
		if(~PINA&(1<<0))
		string_to_LCD("pressed    ");
		else //���� ��� - not pressed
		string_to_LCD("not pressed");
	}
}
//������: �������� �� ������� ����� ���������� Y ���������. 
// ������������� � Proteus