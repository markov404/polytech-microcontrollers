/*
 * Joystick.c
 * На дисплей выводится координата X джойстика
 *  Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
float cod;
char str[12];//Массив для вывода результата на дисплей
//Инициализация АЦП
void ADC_ini(void)
{
	ADCSRA|=(1<<ADEN);//Включение АЦП
	ADCSRA|=(1<<ADPS1)|(1<<ADPS0);//частота АЦП = 1/8 проц. частоты
	ADMUX|=(1<<REFS0);//Опорное напряжение берется от AVCC;
	
}
//Функция преобразования АЦП
void ADCconvert(void)
{
	ADCSRA|=(1<<ADSC);//Запуск одиночного преобразования
	while(ADCSRA&(1<<ADSC));//Подождать, пока не завершится преобразование
	cod=ADC;//Запись в переменную содержимое регистра ADC
}

void cod_to_LCD(void)
{
//Вывод кода на дисплей
		sprintf(str,"%.0f",cod);
		string_to_LCD(str);//Вывести массив с результатом на дисплей
		string_to_LCD("     ");//Стереть символы,
		//которые могли остатьсяс прошлого вывода данных	
}

//
int main(void)
{
	//Вывод 0 порта А на вход с подтягивающим резистором
	DDRA&=~(1<<0);
	PORTA|=(1<<0);
	//Инициализация дисплея и встроенного АЦП
	LCD_ini();
	ADC_ini();
	//Вывод подписей на дисплей
	setpos_to_LCD(0,0);
	string_to_LCD("X:");
	setpos_to_LCD(8,0);
	string_to_LCD("Y:");
	setpos_to_LCD(0,1);
	string_to_LCD("Button:");
	//
	while (1)
	{
	//..........Работа с коорд.X................
		//Выбор второго канала мультиплексора 
		ADMUX|=(1<<MUX1);
		ADMUX&=~(1<<MUX0)&~(1<<MUX2)&~(1<<MUX3);
		//Измерение и вывод на дисплей
		ADCconvert();
		setpos_to_LCD(2,0);
		cod_to_LCD();		
	//..........Работа с  коорд.Y.................
		
	//.........Работа с кнопкой джойстика.........
		setpos_to_LCD(7,1);
		//Если кнопка нажата - выводить pressed
		if(~PINA&(1<<0))
		string_to_LCD("pressed    ");
		else //Если нет - not pressed
		string_to_LCD("not pressed");
	}
}
//ЗАДАЧА: Выводить на дисплей также координату Y джойстика. 
// Смоделировать в Proteus