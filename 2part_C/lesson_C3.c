/*
 * lesson_C2.c
 * ���������� ��� ���������� ����������������� �����������
 */ 
#include <avr/io.h>
#define F_CPU 1000000
//
int main(void)
{
	//������ PB2/AIN0 � PB3/AIN1 �� ����� ��� �������������� ���������
	DDRB&=~(1<<2);
	DDRB&=~(1<<3);
	//����� PB6 �� ����� ��� ���������� ������������
	DDRB|=(1<<6);
	//���������� ������� �� ��������� 
	ACSR&=~(1<<ACD);//����� �� ������
	//
	while (1)
	{
	//���� ���������� �� ��������� ����� AIN1 ������ �������� �������� ����������
	if(~ACSR&(1<<ACO))PORTB|=(1<<6);
	else PORTB&=~(1<<6);//� ��������� ������ - ���������
	}
}
//������: ���������� � ���������������� ����� ���������� ��� 1,23� ������ �������� �� PB2.
// (������������ ����������� ������ ���� ��� ���������� 123 ����.� ��� �����������)
//��������� 2 ����������: ������� ����� ����� ����������� ��������� � ��������
//����������, ������� - ����� ����������� � �����.
//������������� � Proteus