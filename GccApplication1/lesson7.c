/*
 * Lesson12.c
 * ���� ��� ������ �������� ����������
 * ������� ����� (������� ��� ��������)
 *  Author: 1
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602wire4.h"
char i,j,color=1;//��������������� ����������
//�������� ���������
int main(void)
{
	//����������� ������
	DDRB&=~(1<<0)&~(1<<3);
	PORTB|=(1<<0)|(1<<3);
	//����������� �����������
	DDRD|=(1<<0)|(1<<1)|(1<<2)|(1<<3);//PD0 - Green, PD1 - Red
	//������������� �������
	LCD_ini();
	//����������� ������� ����
	setpos_to_LCD(0,0);
	string_to_LCD("Choose one color");
	setpos_to_LCD(0,1);
	string_to_LCD("and press enter!");
	_delay_ms(1500);
	//������� �������
	clear_LCD();
	//���� ������ �����
	setpos_to_LCD(1,0);
	string_to_LCD("Red");
	setpos_to_LCD(7,0);
	string_to_LCD("Yellow");
	
	setpos_to_LCD(1,1);
	string_to_LCD("Blue");
	setpos_to_LCD(7,1);
	string_to_LCD("Green");
	//
	while (1)
	{
		//...................��������� ���������� � ��������� ������...........................
		//����������� ������� ������ "Choose"
		if (~PINB&(1<<0) && i==0)
		{
			i=1;
			color++;
			if(color>4)color=1;
		}
		if (PINB&(1<<0))i=0;
		//............................����� ��������� ����� ">"..................................
		switch(color)
		{
			case 1: 
				//��������� ������ ���������
				setpos_to_LCD(0,0);
				sendsymbol_to_LCD(0x3E);//">"
				//������� ����������� ���������
				setpos_to_LCD(6,1);
				sendsymbol_to_LCD(0x20);//" " - ��� �������
			break;
				//����� �� ��������
			case 2:
				setpos_to_LCD(6,0);
				sendsymbol_to_LCD(0x3E);
				setpos_to_LCD(0,0);
				sendsymbol_to_LCD(0x20);
			break;
			
			case 3:
				setpos_to_LCD(0,1);
				sendsymbol_to_LCD(0x3E);//">"
				//������� ����������� ���������
				setpos_to_LCD(6,0);
				sendsymbol_to_LCD(0x20);//" " - ��� �������
			break;
			
			case 4:
			setpos_to_LCD(6,1);
			sendsymbol_to_LCD(0x3E);//">"
			//������� ����������� ���������
			setpos_to_LCD(0,1);
			sendsymbol_to_LCD(0x20);//" " - ��� �������
			break;
		}
		//....................��������� ������� ����� ��� ������� "Enter"..........................
		if(~PINB&(1<<3))
		{
		switch(color)
			{
			case 1:	PORTD|=(1<<1);//Red
			PORTD&=~(1<<0)&~(1<<2)&~(1<<3);//�������� ������ �����
			break;
			case 2: PORTD|=(1<<0);//Yellow
			PORTD&=~(1<<1)&~(1<<2)&~(1<<3);//�������� ������ �����
			break;
			case 3: PORTD|=(1<<2);
			PORTD&=~(1<<1)&~(1<<0)&~(1<<3);
			break;
			case 4: PORTD|=(1<<3);
			PORTD&=~(1<<1)&~(1<<0)&~(1<<2);
			break;
			}
			
		}
	}
}
//������: �������� ����� � ������� ����������
//������������� � Proteus