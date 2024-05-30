/*
 * Joystick.c
 * На дисплей выводится координата X и Y джойстика
 *  Author: 1
 */ 
#include <avr/io.h>
#include "lcd1602wire4.h"
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>

float cod_x, cod_y;
char str[12]; // Массив для вывода результата на дисплей

// Инициализация АЦП
void ADC_ini(void)
{
    ADCSRA |= (1 << ADEN); // Включение АЦП
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // частота АЦП = 1/8 проц. частоты
    ADMUX |= (1 << REFS0); // Опорное напряжение берется от AVCC
}

// Функция преобразования АЦП
float ADCconvert(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Выбор канала
    ADCSRA |= (1 << ADSC); // Запуск одиночного преобразования
    while (ADCSRA & (1 << ADSC)); // Подождать, пока не завершится преобразование
    return ADC; // Вернуть результат
}

void cod_to_LCD(float cod, uint8_t pos_x, uint8_t pos_y)
{
    // Вывод кода на дисплей
    sprintf(str, "%.0f", cod);
    setpos_to_LCD(pos_x, pos_y);
    string_to_LCD(str); // Вывести массив с результатом на дисплей
    string_to_LCD("     "); // Стереть символы, которые могли остаться с прошлого вывода данных
}

int main(void)
{
    // Вывод 0 порта А на вход с подтягивающим резистором
    DDRA &= ~(1 << 0);
    PORTA |= (1 << 0);
    // Инициализация дисплея и встроенного АЦП
    LCD_ini();
    ADC_ini();
    // Вывод подписей на дисплей
    setpos_to_LCD(0, 0);
    string_to_LCD("X:");
    setpos_to_LCD(8, 0);
    string_to_LCD("Y:");
    setpos_to_LCD(0, 1);
    string_to_LCD("Button:");
    
    while (1)
    {
        // Работа с координатой X
        cod_x = ADCconvert(2); // Выбор второго канала мультиплексора
        cod_to_LCD(cod_x, 2, 0); // Измерение и вывод на дисплей координаты X
        
        // Работа с координатой Y
        cod_y = ADCconvert(3); // Выбор третьего канала мультиплексора
        cod_to_LCD(cod_y, 10, 0); // Измерение и вывод на дисплей координаты Y
        
        // Работа с кнопкой джойстика
        setpos_to_LCD(7, 1);
        // Если кнопка нажата - выводить pressed
        if (~PINA & (1 << 0))
            string_to_LCD("pressed    ");
        else // Если нет - not pressed
            string_to_LCD("not pressed");
        
        _delay_ms(500); // Небольшая задержка для удобства чтения данных на дисплее
    }
}
//ЗАДАЧА: Выводить на дисплей также координату Y джойстика.
// Смоделировать в Proteus
