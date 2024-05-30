/*
 * lcd1602wire4.c
 *
 * Created: 14.11.2016 8:51:21
 *  Author: 1
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD1602wire4.h"
//������ ������ #define ��� ������� ���������� ��������
#define LCD_Port PORTA
#define LCD_Port_out DDRA|=0xF0 //��������� �� ����� ������ ������� ��������.
#define E_out DDRA|=(1<<3)
#define E_1 PORTA|=(1<<3)
#define E_0 PORTA&=~(1<<3)
#define RS_out DDRA|=(1<<2)
#define RS_1 PORTA|=(1<<2)
#define RS_0 PORTA&=~(1<<2)
//
int cod;// ���������� � ������� ������������ ��������� ��������������
//������� �������� ����������� ������ ��� �������������
void halfbytecommand(unsigned halfbyte)
{
RS_0;//��������� RS=0 - �������� �������
E_1;//E=1;
_delay_us(50);
LCD_Port&=0x0F;//������� ������� ����
LCD_Port|=halfbyte&0xF0;//������� ������ � ������� ����
_delay_us(50);
E_0;//E=0;
_delay_us(50);	
}
//������� �������� �����
void sendbyte_to_LCD(unsigned char byte, unsigned char RS)
{
	if (RS==0)RS_0;//���� RS=0 - �������� �������
	else RS_1;//���� RS=1 - �������� ������
	//�������� ������� �������� �����
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//������� ������� ����
	LCD_Port|=byte&0xF0;//������� ������ � ������� ����
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
	//�������� ������� �������� �����
	byte=byte<<4;//�������� �� 4 ������� ������� �������� �����
	E_1;//E=1;
	_delay_us(50);
	LCD_Port&=0x0F;//������� ������� ����
	LCD_Port|=byte&0xF0;//������� ������ � ������� ����
	_delay_us(50);
	E_0;//E=0;
	_delay_us(50);
}
//������������� �������
void LCD_ini(void)
{
	LCD_Port_out;//��������  ���� ������� �� �����
	LCD_Port=0x00;//������� ���� �������
	RS_out;//����� ���������� RS �� �����
	E_out;//����� ���������� E �� �����
	//��������� ����������� ���������� (����� ������ ������� ��������)
	_delay_ms(30);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00110000);
	_delay_us(41);
	halfbytecommand(0b00100000);
	_delay_us(41);
	//��������� �������
	sendbyte_to_LCD(0b00101000,0);//��������� 4-������ �������� ������ � 1-� ���� ����������
	_delay_us(1);
	sendbyte_to_LCD(0b00001100,0);//������� ��������. ������� ���
	_delay_us(1);
}
//��������� ������� � ��������� �������
void setpos_to_LCD(unsigned char X, unsigned char Y)
{
	char adress;
	adress=(0x40*Y+X)|0b10000000;
	sendbyte_to_LCD(adress,0);
}
//����� ������ �� �������
void string_to_LCD(char str1[])
{
	wchar_t n;//���������� ��� ������
	for(n=0; str1[n]!='\0';n++)sendbyte_to_LCD(str1[n],1);//���������� ��� ������� ��
	//������� str1[] �� �������, ���� ������� � ��� �� ���������� str1[n]!='\0'
}
//������� �������� ������� �� �������
void sendsymbol_to_LCD(unsigned char symbol)
{
	sendbyte_to_LCD(symbol,1);
}
//����� ������� ������� ������ ������ �� 1 �������
void move_screen_right(void)
{
	sendbyte_to_LCD(0b00011100,0);
}
//����� ������� ������� ������ ����� �� 1 �������
void move_screen_left(void)
{
	sendbyte_to_LCD(0b00011000,0);
}
//����� ������� ������
void move_cursor_right(void)
{
	sendbyte_to_LCD(0b00010100,0);
}
//����� ������� �����
void move_cursor_left(void)
{
	sendbyte_to_LCD(0b00010000,0);
}
//�������� �������
void clear_LCD(void)
{
	sendbyte_to_LCD(0b00000001,0);
	_delay_ms(2);//����� ����������� ��� �������
}
//�������� ������
void visible_cursor(void)
{
sendbyte_to_LCD(0b00001111,0);
_delay_ms(2);//����� ����������� ��� �������	
}