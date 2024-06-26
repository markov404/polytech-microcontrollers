/*
 * lesson_B1.c
 * ������ �� ���������� ���
 * ��������� ���������� �� �������
 * ����������� LM335
 * Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
float cod,volt, temp;
char str[12];//������ ��� ������ ���������� �� �������
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
	string_to_LCD("Cod:");
	setpos_to_LCD(0,1);
	string_to_LCD("Temp:");
	
	//
	while (1)
	{
		//������ ��������������
		ADCconvert();
		//����� ���� �� �������
		setpos_to_LCD(5,0);
		sprintf(str,"%.0f",cod);
		string_to_LCD(str);//������� ������ � ����������� �� �������
		string_to_LCD("     ");//������� �������,  
		//������� ����� ��������� �������� ������ ������
		//�������������� ���� � �������� ����������
		volt=cod*0.00489;//volt=(cod*5/1024)
		temp = (volt * 100) - 273;
		//����� ���������� �� �������
		setpos_to_LCD(5,1);
		sprintf(str,"%.2f",temp);
		string_to_LCD(str);//������� ������ � ����������� �� �������
		string_to_LCD("");
	}
}
//������: �������� �� ������ ������ ������� �� ����������
//�� �������, � ����������� ��������������� ����� ����������
//������ ���������� � PA0
//������������� � Proteus
