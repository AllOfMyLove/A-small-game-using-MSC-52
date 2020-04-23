#include "reg52.h"
#include "LCD_func.h"
#include "keyboard_func.h"
#include "interrupt_func.h"
#include "random_func.h"

#define uchar unsigned char
extern void delay500ms(void);

// ��ʼ��Ӳ������
void init()
{
    init_LCD();         // LCD ��ʼ��
    init_ex0();         // ���ж�0
    init_ex1();
    init_TIM_0();
    init_TIM_1();       // Ϊ�˲��������
    init_random(TL1);
}

uchar random_num = 0;   // �����

void main()
{
    init();
    // ��������
    display_LCD(0x80,"Welcome");
    delay500ms();
    display_LCD(0x80,"Score:   ");
    while(1)
    {
        // ���ö�ʱ����������������������ж�����
        random_num = random();
    }
}