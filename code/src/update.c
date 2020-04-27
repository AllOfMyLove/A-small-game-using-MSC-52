#include "reg52.h"
#include "LCD_func.h"
#include "keyboard_func.h"
#include "interrupt_func.h"
#define uchar unsigned char

extern uchar random_num;


uchar score = 0;    // ��¼�÷�

uchar decode = 0;   // ���������Ӧ�ļ��̼�����ı���
                    // ������LED���룺
                    //   eg). 0b 10111000  ��ʾ�����е�����

uchar code_dic[]   /* �����ֵ�*/
    = {0xe1,0xb4,0xe2,0xb2,0xd1,0xd4,0xd8,0xe8,0x72,0xb1,0xb8,0x71,0xd2,0x74,0xe4,0x78};


// ÿ�����Ӹ�����Ϣ
void update()
{
    // �������
    uchar i = 0, j = 0;         // ѭ������
    static uchar error = 0;     // �������

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
                score++;        // ��⵽��ȷ���������·���
                error = 0;      // ��մ������
                P0 = 0x00;      // �ر� LED ����
                goto LABAL;     // ֱ����ת��������Ļ������ʾ
            }
        }
    }
    error++;
    if (error>3)
    {
        LCD_clear(0);
        LCD_display(0x80,"FAIL!");
        while(1);
    }

    // ˢ����Ļ
    LABAL:LCD_display(0xC2,uchar2string(score));
}