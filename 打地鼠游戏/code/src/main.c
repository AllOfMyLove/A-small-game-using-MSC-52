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
    LCD_init();         // LCD ��ʼ��
    EX0_init();         // ���ж�0
    EX1_init();
    TIM_0_init();
    TIM_1_init();       // Ϊ�˲��������
    init_random(TL1);
}

uchar random_num = 0;   // �����

void main()
{
    init();
    // ��������
    LCD_display(0x80,"Welcome");
    delay500ms();
    LCD_display(0x80,"Score:   ");
    while(1)
    {
        // ���ö�ʱ����������������������ж�����
        random_num = random();
    }
}