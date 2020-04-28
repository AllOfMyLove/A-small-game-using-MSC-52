#include "reg52.h"
#include "LCD_func.h"
#include "keyboard_func.h"
#include "interrupt_func.h"
#include "random_func.h"
#define uchar unsigned char
void update(void);
extern uchar random_num;
uchar score = 0;                        // ��¼�÷�


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
// �������ÿ�����Ӹ���
void TIM_0_isr() interrupt 1
{
    static uchar count = 0;             // ������������ count = 10 ʹ��ʾ����
    TH0 = (65536 - 50000) / 256;        // ��ʱ���ֶ���װ
    TL0 = (65536 - 50000) % 256;
    count++;
    if (count==10)                      // ����ʱ�䵽
    {
        count = 0;                      // ��ձ�־λ
        update();                       // ����update������ִ�����߼�
    }
}

// update ����ʵ��
// ÿ�����Ӹ�����Ϣ
void update()
{
    // �������
    uchar i = 0, j = 0;                 // ѭ������
    static uchar error = 0;             // �������
    

    uchar decode = 0;                   // ���������Ӧ�ļ��̼�����ı���
                                        //   eg). 0b 10111000  ��ʾ�����е�����

    uchar code_dic[]                    /* �����ֵ�*/
        = {0xe1,0xb4,0xe2,0xb2,0xd1,0xd4,0xd8,0xe8,0x72,0xb1,0xb8,0x71,0xd2,0x74,0xe4,0x78};

    // ��ȡ�����������ȡ�������Ӧ����
    if(random_num<0 || random_num>15)
        random_num = 0;
    decode = code_dic[random_num];

    // ��������
    P0 = decode;

    // ����ɨ����̣�����⵽��Ӧ����ʱ��ȡ�÷���
    // ��������û�а��԰�����������Ϸ
    for (i=0;i<255;i++)
    {
        for (j=0;j<150;j++)
        {
            if(decode == KEYBOARD_get_key())
            {
                score++;                // ��⵽��ȷ���������·���
                error = 0;              // ��մ������
                P0 = 0x00;              // �ر� LED ����
                goto LABAL;             // ֱ����ת��������Ļ������ʾ
            }
        }
    }
    error++;
    if (error>3)
    {
        LCD_clear(0);                   // ���LCD
        P0 = 0x00;                      // �ر� LED ����
        LCD_display(0x80,"FAIL!");
        while(1);
    }

    // ˢ����Ļ
    LABAL:LCD_display(0xC2,uchar2string(score));
}