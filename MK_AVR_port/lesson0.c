/*
 * lesson0.c
 * �� ������� ������ ���������� ����� ���������, � ������� ������
 *  Author: 1
 */  
#include <avr/io.h>
//�������� ���������
int main(void)
{
	DDRC|=(1<<2);//����� PC2 �� ����� (������� ���������)
	DDRD|=(1<<4);//����� PD4 �� ����� (����� ���������)
	DDRB&=~(1<<2);//����� PB2 �� ���� (������ K1)
	PORTB|=(1<<2);//������������� �������� �� PB2
	//
	while (1)
	{
		if(~PINB&(1<<2))//���� ������ K1 ������
		{
		PORTD|=(1<<4);//������ ����� ���������
		PORTC&=~(1<<2);//�������� ������ ���������
		}
		else//���� ������ K1 ������
		{
		PORTD&=~(1<<4);//�������� ����� ���������
		PORTC|=(1<<2);//������ ������ ���������
		}
	}
}
//������ 1: �������� ������ �� PA4 � ��������� �� PB6. 
//          �� ������� ������ K2 ��������� �� PB6 ������ �������
//������ 2: �� ������� ������ K1 ��� ���������� ������ ����������,
//          �� ������� ������ K2 - �������.
//������ 3: �� ������� ������ K2 ��� ���������� ������ ����������,
//          �� � ������� - �������. ����� �������� ������ ��������,
//          ���� K1 ������
//������������� � Proteus