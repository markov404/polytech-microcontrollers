/*
 * lesson13.c
 *
 * ���� ������ ��� ����� � ��������
 *  Author: 1
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602wire4.h"
unsigned char n,i=-1;//��������������� ����������
char Cod_preset[]={4,5,7,8,9,0};//Macc�� c ������������� �����
char Cod_input[6];//������ � ������� �����
//������������� ������
void port_ini(void)
{
//����������� �������� �� �����
DDRD|=(1<<0)|(1<<1)|(1<<2);
//����������� ����� �� ���� � ���������
DDRD&=~(1<<3)&~(1<<4)&~(1<<5)&~(1<<6);
PORTD|=(1<<3)|(1<<4)|(1<<5)|(1<<6);	
DDRC|=(1<<2);
}
//����� �������
int Keypad_scan()
{
n=10;//�� ���� ������ �� ������
//...............����� ������� �������............................
PORTD&=~(1<<0);
PORTD|=(1<<1)|(1<<2);
if(~PIND&(1<<3))n=1;
if(~PIND&(1<<4))n=4;
if(~PIND&(1<<5))n=7;
if(~PIND&(1<<6))n=0x2A-0x30;//��������� "*" 0x2A
//...............����� ������� �������............................
PORTD&=~(1<<1);
PORTD|=(1<<0)|(1<<2);	
if(~PIND&(1<<3))n=2;
if(~PIND&(1<<4))n=5;
if(~PIND&(1<<5))n=8;
if(~PIND&(1<<6))n=0;
//...............����� �������� �������............................
PORTD&=~(1<<2);
PORTD|=(1<<0)|(1<<1);
if(~PIND&(1<<3))n=3;
if(~PIND&(1<<4))n=6;
if(~PIND&(1<<5))n=9;
if(~PIND&(1<<6))n=0x23-0x30;//������� "#" 0x23
return n;
}
//�������� ���������
int main(void)
{
	//������������� ������
	port_ini();
	//������������� �������
	LCD_ini();
	//�������� ������
	visible_cursor();
	//������� �������
	clear_LCD();
	setpos_to_LCD(0,0);
	string_to_LCD("Enter password:");
	setpos_to_LCD(5,1);
	//
	while (1)
	{
	//����� �������
	n=Keypad_scan();
//...................................................................
//........��������� ������� ������ ���� ���� ������� ������..........
	if(n != 10)
	{
	i++;//������� ����� ��������� ��������
	//��������� ������ � ������� �� �������
	sendbyte_to_LCD(0x2A,1);
	_delay_ms(300);	
	Cod_input[i]=n;
	//...............�������� ����� ����� ������.......................
		if(i==5)//����� ����� ������� ������ �������� ����
		{
		i=-1;//�������� ����� ������� ������
		//������� � 5-�� ������� 2-� ������ 
		setpos_to_LCD(5,1); //(0 - ������ ������, 1 - ������)
		//�������� �������� ������
		if(Cod_preset[0]==Cod_input[0] &&
		   Cod_preset[1]==Cod_input[1] &&
		   Cod_preset[2]==Cod_input[2] &&
		   Cod_preset[3]==Cod_input[3] &&
		   Cod_preset[4]==Cod_input[4] &&
			Cod_preset[5]==Cod_input[5])
			{	
			string_to_LCD("TRUE!   ");
			PORTC|=(1<<2);
			_delay_ms(500);
			PORTC&=~(1<<2);
				
			}
		else string_to_LCD("FALSE!   ");
		_delay_ms(1000);//���������� ��������� � 
		//��������/���������� ������ � ������� 1 �������
		//�������� ������� � ������ ������ ������:
		clear_LCD();
		setpos_to_LCD(0,0);
		string_to_LCD("Enter password:");
		setpos_to_LCD(5,1);
		
		}
//.....................................................................
//.....................................................................
	}	
	}
}
//������: ������� ������ �� 6 ��������
//��������� 1 ��������� (���������� ����� ������ ������)
//������ ���� ��������� ����� ������� ����� ������ �������
//����������� ���� ������ �� ������� �������� �����������
//������������� � Proteus