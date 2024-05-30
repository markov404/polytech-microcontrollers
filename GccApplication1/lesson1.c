/*
 * lesson1.c
 * ���������� ���������� ���������� ������ ���� �� �������
 *  Author: 1
 */ 
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
//�������� ���������
int main(void)
{
	DDRD=0xFF;//��������� ����� D �� �����
	signed char i;//���������� i (����� ���� �� -128 �� +127)
	//
//Zadanie1
	while(1)
	{
		for(i=0;i <= 7;i++)//����������� �� ��� ���, ���� i ������ ��� ����� 7
		{
			PORTD|=(1<<i);
			_delay_ms(250);
			PORTD = 0x00;
		}
	}

//Zadanie 2
/*
	while (1)
	{
		for(i=0;i<=7;i++)//����������� �� ��� ���, ���� i ������ ��� ����� 7
		{
		PORTD|=(1<<i);
		_delay_ms(250);
		}
		for(i=7;i>=0;i--)//����������� �� ��� ���, ���� i ������ ��� ����� 7
		{
			PORTD&=~(1<<i);
			_delay_ms(250);
		}
	}
*/
//Zadanie3
/*
	while (1)
	{
		for(i=0;i<=7;i++)//����������� �� ��� ���, ���� i ������ ��� ����� 7
		{
			PORTD|=(1<<i);
			_delay_ms(250);
			PORTD&=~(1<<i);
		}
		for (i = 7; i >= 0; i--)
		{
			PORTD|=(1<<i);
			_delay_ms(250);
			PORTD&=~(1<<i);
		}
		
	}
*/
//Zadanie4
/*
while (1)
{
	for(i=0;i<=6;i++)//����������� �� ��� ���, ���� i ������ ��� ����� 7
	{
		PORTD|=(1<<i);
		PORTD|=(1<<(i + 1));
		_delay_ms(250);
		PORTD=0x00;
	}
	for (i = 6; i >= 0;i--)
	{
		PORTD|=(1<<i);
		PORTD|=(1<<(i + 1));
		_delay_ms(250);
		PORTD=0x00;
	}
	
}
/*
while(1)
{
	for(i = 0; i <= 3; i++)
	{
		PORTD|=(1<<i);
		PORTD|=(1<<(7-i));
		_delay_ms(250);
		PORTD=0x00;
	}
	for(i = 3; i >= 0; i--)
	{
		PORTD|=(1<<i);
		PORTD|=(1<<(7 - i));
		_delay_ms(250);
		PORTD=0x00;
	}
	
*/
PORTD=0x00;
}
//������ 1: ���������� ���������� ������ ���������� ����� ����� �� ������� � �������
//������ 2: ���������� ���������� ������ ���������� ������ ����, � ����� ������� ����� ����� �� �������
//������ 3: ������ ���������� ������ ����, ����� ����� ����� 
//������ 4: ��� ������� ���������� ������ ����, ����� ����� �����
//������ 5: ��� ������� �������� � ������ � ����������

