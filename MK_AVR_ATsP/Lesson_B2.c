/*
 * lesson_B2.c
 * Работа со встроенным АЦП
 * Определение нажатия кнопки при 
 * использовании ступенчатого реостата
 * Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
float cod,volt;
char str[12];//Массив для вывода результата на дисплей
char n;//Вспомогательная переменная
//Инициализация АЦП
void ADC_ini(void)
{
	ADCSRA|=(1<<ADEN);//Включение АЦП
	ADCSRA|=(1<<ADPS1)|(1<<ADPS0);//частота АЦП = 1/8 проц. частоты
	ADMUX|=(1<<REFS0);//Опорное напряжение берется от AVCC;	
	ADMUX|=(1<<MUX0)|(1<<MUX1);//Мультиплексор АЦП к PA3/ADC3
}
//Функция преобразования АЦП
void ADCconvert(void)
{
	ADCSRA|=(1<<ADSC);//Запуск одиночного преобразования
	while(ADCSRA&(1<<ADSC));//Подождать, пока не завершится преобразование
	cod=ADC;//Запись в переменную содержимого регистра ADC
}
//
int main(void)
{
	//Инициализация дисплея и встроенного АЦП
	LCD_ini();
	ADC_ini();
	//Вывод подписей на дисплей
	setpos_to_LCD(0,0);
	string_to_LCD("Voltage:");
	setpos_to_LCD(0,1);
	string_to_LCD("Button:");
	//
	
	//
	while (1)
	{
		//Запуск преобразования
		ADCconvert();
		volt=cod*0.00488;//volt=(cod*5/1024)
		//Вывод напряжения на дисплей
		setpos_to_LCD(9,0);
		sprintf(str,"%.2f",volt);
		string_to_LCD(str);//Вывести массив с результатом на дисплей
		string_to_LCD("     ");
		//Определение нажатой кнопки
		if(volt>4)n=0;
		if(volt>0.4 && volt<0.5)n=1;
		if(volt>0.8 && volt<0.9)n=2;
		//Вывод номера нажатой кнопки
		setpos_to_LCD(8,1);
		sendbyte_to_LCD(n+0x30,1);
	}
}
//ЗАДАЧА: определять нажатие четырех кнопок 
//измерения производить по входу PA5/ADC5
//Смоделировать в Proteus