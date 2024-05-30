/*
 * Lesson_B3.c
 * Работа со встроенным АЦП
 * Измерение напряжения:
 * V1 от 0 до 5В
 * V2 от 0 до 20В
 * V3 от 0 до 99В
 * V4 от 0 до 30В
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>

long int cod, volt;
char str[12]; // Массив для вывода результата на дисплей

// Инициализация АЦП
void ADC_ini(void)
{
    ADCSRA |= (1 << ADEN); // Включение АЦП
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // частота АЦП = 1/8 проц. частоты
    ADMUX |= (1 << REFS0); // Опорное напряжение берется от AVCC
}

// Функция преобразования АЦП
void ADCconvert(void)
{
    ADCSRA |= (1 << ADSC); // Запуск одиночного преобразования
    while (ADCSRA & (1 << ADSC)); // Подождать, пока не завершится преобразование
    cod = ADC; // Запись в переменную содержимое регистра ADC
}

// Функция вывода напряжения на дисплей
void Volt_to_Display(void)
{
    char dig1, dig2, dig3;
    // Разбиение значения напряжения по цифрам
    dig1 = volt / 10000; // Десятки
    dig2 = volt / 1000 % 10; // Единицы
    dig3 = volt / 100 % 10; // Десятые
    // Вывод цифр напряжения на дисплей
    sendsymbol_to_LCD(dig1 + 0x30);
    sendsymbol_to_LCD(dig2 + 0x30);
    sendsymbol_to_LCD(0x2E); // Вывод десятичной точки "."
    sendsymbol_to_LCD(dig3 + 0x30);
}

int main(void)
{
    // Инициализация дисплея и встроенного АЦП
    LCD_ini();
    ADC_ini();
    // Вывод подписей на дисплей
    setpos_to_LCD(0, 0);
    string_to_LCD("V1:");
    setpos_to_LCD(8, 0);
    string_to_LCD("V2:");
    setpos_to_LCD(0, 1);
    string_to_LCD("V3:");
    setpos_to_LCD(8, 1);
    string_to_LCD("V4:");
    
    while (1)
    {
        // Работа с V1
        ADMUX = (ADMUX & 0xF0) | 0x05; // Выбор PA5/ADC5
        ADCconvert();
        volt = cod * 4.89; // volt = (cod * 5 / 1023) * 1000
        volt = volt * 10; // Для V1 используется делитель напряжения на 10
        setpos_to_LCD(3, 0);
        Volt_to_Display();

        // Работа с V2
        ADMUX = (ADMUX & 0xF0) | 0x06; // Выбор PA6/ADC6
        ADCconvert();
        volt = cod * 4.89; // volt = (cod * 5 / 1023) * 1000
        volt = volt * 4; // Для V2 используется делитель напряжения на 4
        setpos_to_LCD(11, 0);
        Volt_to_Display();

        // Работа с V3
        ADMUX = (ADMUX & 0xF0) | 0x07; // Выбор PA7/ADC7
        ADCconvert();
        volt = cod * 4.89; // volt = (cod * 5 / 1023) * 1000
        volt = volt * 20; // Для V3 используется делитель напряжения на 20
        setpos_to_LCD(3, 1);
        Volt_to_Display();

        // Работа с V4
        ADMUX = (ADMUX & 0xF0) | 0x04; // Выбор PA4/ADC4
        ADCconvert();
        volt = cod * 4.89; // volt = (cod * 5 / 1023) * 1000
        volt = volt * 6.1; // Для V4 используется делитель напряжения на 6.1
        setpos_to_LCD(11, 1);
        Volt_to_Display();
    }
}
//ЗАДАЧА: Помимо V1 и V2 измерять напряжения V3 и V4
//V3 в пределах от 0 до 99В
//V4 в пределах от 0 до 30В
//Смоделировать в Proteus