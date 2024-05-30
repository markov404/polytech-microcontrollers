/*
 * LessonC2.c
 *
 * Created: 18.10.2020 17:33:11
 *  Author: 1
 */ 
 #define F_CPU 1000000
 #include <util/delay.h>
 #include <avr/io.h>
 #include <avr/interrupt.h> //���������� ���������� ����������
 #include "LCD1602wire4.h"
 char i=0,j=0;
 int angle=0;//������� ��������� ���� ����������������
char k = 0;
int c, c1 = 1000;
int u, u1 = 1000;
 //������������� ������
 void Port_ini(void)
 {
	//������������� ������� ��� �������
	 DDRD&=~(1<<3)&~(1<<4);
	 PORTD|=(1<<3)|(1<<4);
 }
 //��������� ����������
 void interrupt_ini()
 {
	 sei();//���������� ���������� ����������
	 GICR|=(1<<INT1);//��������� ���������� ��� ����� INT1
	 //������������ �������� ���������� ��� ����� INT1
	 // �� ���������� ������ ISC10=0 ISC11=1
	 MCUCR|=(1<<ISC11);                 
 }
//������� ������ �������� ��������� �� �������

 void angle_to_Display(void)
 {
	 char dig1,dig2,dig3;
	 //��������� �������� �������� ��������� �� ������
	 dig1 = angle/100;    //�������
	 dig2 = angle/10%10;	//�������
	 dig3 = angle%10;  //�������
	 //���������� ����� �������� ��������� �� �������
	 setpos_to_LCD(6,0);
	 sendsymbol_to_LCD(dig1+0x30);
	 sendsymbol_to_LCD(dig2+0x30);
	 sendsymbol_to_LCD(dig3+0x30);
 }
 //������� ��������� ���������� �� ������ INT1 (PD3)
 ISR(INT1_vect)
 {
		 _delay_us(50);
		 if(~PIND&(1<<4))//���� �� ������ PD4 ���.0
		 {
			 angle=angle+1;        // ���������������� �
			 if(angle>360)	// ���� �>345, �� a=0;
			 {
				 angle=0;
			 }
			 if (u == u1)
			 {
				 
				 u = angle;
				 u1 = u - 1;
			 }
			 if(u1 == angle)
			 {
				 k += 1;
			 }
			 c = 1000;
			 c1 = 1000;
			 setpos_to_LCD(10,1);
			 string_to_LCD("Right");
			 setpos_to_LCD(14, 0);
			 sendsymbol_to_LCD(k+0x30);
			 		 
		 }
		 else
		 {
			 angle=angle-1;           // ���������������� �
			 if(angle<0)	   // ���� �<0, �� a=345;
			 {
				 angle=360;
			 }
			 if (PIND&(1<<4) && c == c1)
			 {
				 c = angle;
				 c1 = c + 1;
			 }
			 if(c1 == angle)
			 {
				 k += 1;
			 }
			 u = 1000;
			 u1 = 1000;
			 setpos_to_LCD(10,1);
			 string_to_LCD("Left ");
			 setpos_to_LCD(14, 0);
			 sendsymbol_to_LCD(k+0x30);
		 }
		 //����� ������� ������ �������� ��������� �� �������
		 angle_to_Display();
 }
//������ �������������� ������� (�������) � ������ �������
  void send_gradus(void)
  {
	  //������ "������"
	  char gradus[8]={0b01110,
		              0b01010,
		              0b01010,
		              0b01110,
		              0b00000,
		              0b00000,
		              0b00000,
	                  0b00000};//������ "������"
	  //����� ������� CGRAM: (0x00 - �������, 0x08 - ������, 
	  //0x08*2=0x10 - ������ 0x08*3=0x18 - ������ � �.�. )
	  sendbyte_to_LCD(0x40|0x08,0); //������� ������ �������
	  //������ ������� gradus � ������ ������� CGRAM 5x8 ��������
	  for (unsigned char i = 0; i < 8; i++)sendbyte_to_LCD(gradus[i],1);	  
  }
 //�������� �������
 int main(void)
 {	 
	 interrupt_ini();//��������� ����������
	 LCD_ini();//��������� �������
	 Port_ini();//������������� ������
	 //����� �������� �� �������
	 setpos_to_LCD(0,0);
	 string_to_LCD("Angle:");
	 setpos_to_LCD(9,0);//������� �� �������, ���� ������������ ������
	 sendbyte_to_LCD(0x01,1);//�������� ������ ������ �� CGRAM �� �������
	 send_gradus();//����� ������� ������� �� �������
	 setpos_to_LCD(0,1);
	 string_to_LCD("Direction:");
	 setpos_to_LCD(12, 0);
	 string_to_LCD("k:");
	 //����������� ����
	 while(1)
	 {
	 //������ ����	
	 }
 }
 //������: 1)�������� �� ������� � ����������� �� 
 //          ����������� ��������: <<left ��� right>>
 //        2)������������� ����� ������ �������� ����
 //          � �������� ��� �� �������. 
 //        3)� ��������� Proteus � ���������� ������-��������
 //          �������� ����� ��������� �� ������ � 24 �� 360.
 //          ��������� ������� ��������� � ��������� �� 1 �������
 //������������� � Proteus