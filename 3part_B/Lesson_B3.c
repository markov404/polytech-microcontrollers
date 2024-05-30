/*
 * Lesson_B3.c
 * ������ �� ���������� ���
 * ��������� ����������:
 * V1 �� 0 �� 5�
 * V2 �� 0 �� 20�
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
long int cod,volt;
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
//������� ������ ���������� �� �������
void Volt_to_Display(void)
{
char dig1,dig2,dig3;
//��������� �������� ���������� �� ������
dig1 = volt/10000;    //�������
dig2 = volt/1000%10;	//�������
dig3 = volt/100%10;  //�������
//����� ���� ���������� �� �������
sendsymbol_to_LCD(dig1+0x30);
sendsymbol_to_LCD(dig2+0x30);
sendsymbol_to_LCD(0x2E);//����� ���������� �����"."
sendsymbol_to_LCD(dig3+0x30);	
}
//
int main(void)
{
	//������������� ������� � ����������� ���
	LCD_ini();
	ADC_ini();
	//����� �������� �� �������
	setpos_to_LCD(0,0);
	string_to_LCD("V1:");
	setpos_to_LCD(8,0);
	string_to_LCD("V2:");
	//
	while (1)
	{
//.............................������ � V1...........................................
		//����������� � V1                      ����� PA5/ADC5                       
		ADMUX|=(1<<MUX0)|(1<<MUX2);     //    MUX2  MUX1   MUX0 
		ADMUX&=~(1<<MUX1);              //      1     0      1
		//���������, �������������� ���� � ����������, ����� �� �������
		ADCconvert();
		volt=cod*4.89;//volt=(cod*5/1023)*1000
		volt=volt*10;//��� V1 ����������� �������� ���������� �� 10
		setpos_to_LCD(3,0);
		Volt_to_Display();
//.............................������ � V2...........................................		
		//����������� � V2                      ����� PA6/ADC6    
		ADMUX|=(1<<MUX1)|(1<<MUX2);    //    MUX2  MUX1   MUX0 
		ADMUX&=~(1<<MUX0);             //      1     1      0
		//��������� � ����� �� �������
		ADCconvert();
		volt=cod*4.89;//volt=(cod*5/1023)*1000
		volt=volt*4;//��� V2 ����������� �������� ���������� �� 4
		setpos_to_LCD(11,0);
		Volt_to_Display();
//....................................................................................
	}
}
//������: ������ V1 � V2 �������� ���������� V3 � V4
//V3 � �������� �� 0 �� 99�
//V4 � �������� �� 0 �� 30�
//������������� � Proteus