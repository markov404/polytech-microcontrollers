/*
 * lesson_B2.c
 * ������ �� ���������� ���
 * ����������� ������� ������ ��� 
 * ������������� ������������ ��������
 * Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
float cod,volt;
char str[12];//������ ��� ������ ���������� �� �������
char n;//��������������� ����������
//������������� ���
void ADC_ini(void)
{
	ADCSRA|=(1<<ADEN);//��������� ���
	ADCSRA|=(1<<ADPS1)|(1<<ADPS0);//������� ��� = 1/8 ����. �������
	ADMUX|=(1<<REFS0);//������� ���������� ������� �� AVCC;	
	ADMUX|=(1<<MUX0)|(1<<MUX1);//������������� ��� � PA3/ADC3
}
//������� �������������� ���
void ADCconvert(void)
{
	ADCSRA|=(1<<ADSC);//������ ���������� ��������������
	while(ADCSRA&(1<<ADSC));//���������, ���� �� ���������� ��������������
	cod=ADC;//������ � ���������� ����������� �������� ADC
}
//
int main(void)
{
	//������������� ������� � ����������� ���
	LCD_ini();
	ADC_ini();
	//����� �������� �� �������
	setpos_to_LCD(0,0);
	string_to_LCD("Voltage:");
	setpos_to_LCD(0,1);
	string_to_LCD("Button:");
	//
	
	//
	while (1)
	{
		//������ ��������������
		ADCconvert();
		volt=cod*0.00488;//volt=(cod*5/1024)
		//����� ���������� �� �������
		setpos_to_LCD(9,0);
		sprintf(str,"%.2f",volt);
		string_to_LCD(str);//������� ������ � ����������� �� �������
		string_to_LCD("     ");
		//����������� ������� ������
		if(volt>4)n=0;
		if(volt>0.4 && volt<0.5)n=1;
		if(volt>0.8 && volt<0.9)n=2;
		//����� ������ ������� ������
		setpos_to_LCD(8,1);
		sendbyte_to_LCD(n+0x30,1);
	}
}
//������: ���������� ������� ������� ������ 
//��������� ����������� �� ����� PA5/ADC5
//������������� � Proteus