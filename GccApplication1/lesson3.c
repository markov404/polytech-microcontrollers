/*
 * lesson9.c
 * ������������ ���������
 * �����-���������� ��������������� (���)
 * ������������� ��������� ����������� �����
 * Author: 1
 */
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
int main(void)
{
DDRD=0xFF;
int i=0;
//����������� ����
/*
	while (1)
	{
	//����������� (���������� ����������)
		for(i=0;i<=255;i++)
		{
			PORTD=(255 - i);	
			_delay_us(10);
		}
	}
*/		

	//����������� (���� ����������)
	while(1)
	{
		for(i=255;i>0;i--)
		{
			PORTD=i;
			_delay_us(10);
		}
	}

/*
	while(1)
	{
		for(i=0;i<255;i++)
		{
			if (i < 127)
			{
				PORTD=i;
				_delay_us(10);
			}
			else if (i > 127)
			{
				PORTD = (255 - i);
				_delay_us(10);
				
			}
		}
		
	}
*/
/*
	while(1)
	{
		for(i = 0;i < 255; i++)
		{	
			if (i < 64)
			{
				PORTD = 0;
				_delay_us(10);
			}
			else if(i < 255)
			{
				PORTD = 100;
				_delay_us(10);
			}
			
		}
	}
*/
}
//������: �� ������� �� ������, ������������ � PB3 ������ 
//��������� 3 ���� ��������� ������� � ���:
//������: ����������� (���� ����������)
//������: ����������� �������������� (����������, ����� ���� ����������)
//������: ������������� ��������
//������������� � Proteus
