/*
 * lesson7.c
 * ����������� ���������
 * ������� ���������� ������� �������� ������ �� PD6
 * � ���������� �� 7-���������� ����������
 * Author: 1
 */ 
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>
int main(void)
{
	//������ ����   0     1     2     3     4     5     6     7     8     9
	char  led[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	signed char n=0;//���������� ������� 
	//������������� ������
	DDRC=0b11111111;//��������� �� ���� �
	PORTC=~led[0];//������� 0 �� �������� � ����� ������
	DDRD&=~(1<<6);//����� ��� ����������� ������ (�� ����)
	PORTD|=(1<<6);//����� ��� ����������� ������ (���������� ���������� ������������� ��������)
	//
	while(1)//����������� ����
	{ 
		if(~PIND&(1<<6))
		{
		_delay_ms(200);//�������� �� ������� ���������
			if(~PIND&(1<<6))//���� ������ ������
			{
			n++;
			if(n>9)n=0;//����� ������������� ���������� �������
			PORTC=~led[n];//������ ����� �� ��������� (c ����� ������)
			while(~PIND&(1<<6));//����� ���� ������ ������
			}	
		}		
	}
}
//������: �� ������� ������� ������ PA2 ����� �� ���������� 
//������������� �� 1, � �� ������� ������ PA3 ����������� �� 1
//��������� ���������� �� ���� D
//��������� ����� �� ���������� ������ ������������ �� ���������� ������
//������������� � Proteus