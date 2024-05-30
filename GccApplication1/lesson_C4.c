/*
 * lesson_C3.c
 * ������������� ���������� �� �����������
 */  
#include <avr/io.h>
#define F_CPU 1000000
#include <avr/interrupt.h>
//������ ���������� �� �����������
ISR(ANA_COMP_vect)
{
	PORTB^=(1<<6);//������������� ��������
}
//
int main(void)
{
	//������ PB2/AIN0 � PB3/AIN1 �� ����� ��� �������������� ���������
	DDRB&=~(1<<2);
	DDRB&=~(1<<3);
	//����� PB6 �� ����� 
	DDRB|=(1<<6);
	//
	//������� ����������� ���������� ����������
	sei();
	//��������� ���������� �� ����������� (ACIE=1)
	//��� ��������� ������ ����������� � 0 �� 1 (ACIS0=1,ACIS1=1)
	//���������� � ���������������� ����� ����������� ���������� ��� (ACBG=1)
	ACSR|=(1<<ACIE);
	//������ ����������� ����
	while (1)
	{
	}
}
//������: ���������� � ���������������� ����� ����������� 
//������������ ��� ������� ��� ������ ������������
//��������� ���������� �� ����������� ��� ����� ���������
//��������� ��� ������.
//������������� � Proteus