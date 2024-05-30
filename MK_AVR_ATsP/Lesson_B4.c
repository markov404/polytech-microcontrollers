/*
 * Lesson_B4.c
 * ���������������� ����� ���
 * ��������� ���� ��������
 * � ������� �������� �����
 * ������� ���������� �� 
 * ����������� ��������� U
 */
 #include <avr/io.h>
 #include "lcd1602wire4.h"
 #define F_CPU 8000000
 #include <util/delay.h>
 #include <stdio.h>
 float cod,current;
 //������ ��� ������ ���������� �� �������
 char str[12];
 //������������� ���
 void ADC_ini(void)
 {
	 ADCSRA|=(1<<ADEN);//��������� ���
	 //������� ��� = 1/64 ����. �������
	 ADCSRA|=(1<<ADPS2)|(1<<ADPS1);
	 //������� ���������� ������� ��
	 //����������� ��������� U=2.56�;
	 ADMUX|=(1<<REFS0)|(1<<REFS1);
	 //�������� ����� ��� � ����������������� �������
	 //PA3 - "+", PA2 - "-"  � ��������� � 10 ���
	 ADMUX|=(1<<MUX3)|(1<<MUX2)|(1<<MUX0);
	 //������������ ������ ����������
	 //�������������� �����
	 ADMUX|=(1<<ADLAR);
 }
 //������� �������������� ���
 void ADCconvert(void)
 {
	 //������ ���������� ��������������
	 ADCSRA|=(1<<ADSC);
	 //���������, ���� �� ���������� ��������������
	 while(ADCSRA&(1<<ADSC));
	 //������ � ���������� ����������� �������� ADC
	 cod=ADCH;
 }
 //
 int main(void)
 {
	 //������������� ������� � ����������� ���
	 LCD_ini();
	 ADC_ini();
	 //
	 while (1)
	 {
		 //��������� ��������������
		 ADCconvert();
		 //�������������� ���� � ���
		 current=cod*0.01;//current=(cod*2.56/256)
		 //����� �������� ���� �� �������
		 setpos_to_LCD(0,0);
		 sprintf(str,"I=%.2f",current);
		 //������� ������ � ����������� �� �������
		 string_to_LCD(str);
		 string_to_LCD("A  ");
	 }
 }

//������: ����������� ��������� ���� �� ����� R4 � 
//���������������� ������ ����� �������� ADC1-ADC0 ��������������.
//� �������� �������� ���������� ����������� ���������� � ������ AVcc.
//�������� �� LCD-������� ������ �������� ����������� ����, ����� ���
//� �������� ADCH � �������� ���������� �� �����.
// ������������� � Proteus





 
