#include "reg52.h"
#include "LCD_func.h"
#include "keyboard_func.h"
#include "interrupt_func.h"
#include "random_func.h"
#define uchar unsigned char
extern void update(void);
extern uchar score;


/********************************************************************************************
                                        ��ʱ500ms
********************************************************************************************/
void delay500ms(void)
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}


/********************************************************************************************
                                        ��ͣ�����
********************************************************************************************/
bit is_pause = 0;                       // ��ͣʱ�ı�־λ��is_pause = 1 ��ʾ������ͣ״̬

// INT1 �жϣ��ֶ����õ����ȼ�
void pause() interrupt 2
{
    P0 = 0x00;                          // LED ����Ϩ��
    is_pause = 1;                       // ���±�־λ
    LCD_clear(0);
    LCD_display(0x80,"   PAUSE");       // ���� LCD ��ʾ��
    init_random(TL1);                   // ���»�ȡ�����
    while(is_pause);                    // �� "CONTINUE" ����ǰ����־λһֱΪ 1
                                        //  "CONTINUE" ���º󣬱�־λ���㣬�˳�����ѭ����������Ϸ
}

// INT0 �жϣ��ֶ����ø����ȼ�
void continuee() interrupt 0
{
    if (is_pause == 0)                  // ��֮ǰû�а���"PAUSE"���������κη�Ӧ
        return;
    LCD_clear(0);                       // ������ʾ��������
    LCD_display(0x80,"CONTINUE");
    delay500ms();
    LCD_display(0x80,"Score:     ");    // ��ʾ���ָ���ͣǰ��״̬
    LCD_display(0xC2,uchar2string(score));
    is_pause = 0;                       // ���±�־λ��ʹ֮�˳�pause�ж�
}


/********************************************************************************************
                                    ��������
********************************************************************************************/
uchar count = 0;                        // ������������ count = 10 ʹ��ʾ����

// �������ÿ�����Ӹ���
void TIM_0_isr() interrupt 1
{
    TH0 = (65536 - 50000) / 256;        // ��ʱ���ֶ���װ
    TL0 = (65536 - 50000) % 256;
    count++;
    if (count==10)                      // ����ʱ�䵽
    {
        count = 0;                      // ��ձ�־λ
        update();                       // ����update������ִ�����߼�
    }
}