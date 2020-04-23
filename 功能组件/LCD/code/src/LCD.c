#include "reg51.h"
#include "LCD.h"


void delay()
{
    uchar j=0;
    for(j=0;j<255;j++);
}

void write_char(uchar dat)
{
    // ����ʱ��ͼ
    RS = 1;
    RW = 0;
    E  = 0;
    LCD_PORT = dat;
    delay();
    delay();
    E = 1;
    E = 0;
}

void write_cmd(uchar command)
{
    RS = 0;
    RW = 0;
    E  = 0;
    LCD_PORT = command;
    delay();
    E = 1;
    E = 0;
}

void init_LCD()
{
    write_cmd(0x38);    // ����16��2��ʾ��5��7����8λ���ݽӿ�
    write_cmd(0x0c);    // ���ÿ���ʾ������ʾ���
    write_cmd(0x06);    // дһ���ַ����ַָ���1
    write_cmd(0x01);    // ��ʾ��0������ָ����0
}


/**
 * @brief  ����Ļ����ʾ�ַ���  
 * @param  line: ��Ҫ��ʾ������
 * @param  *str: �ַ������׵�ַ
 */
void display_LCD(uchar line,char *str)
{
    uchar i = 0;
    if (line == 1)
        write_cmd(0x80);         // LCD��һ�е���ʼ��ַ
    if (line == 2)
        write_cmd(0x80+0x40);    // LCD�ڶ��е���ʼ��ַ
    while(str[i]!='\0')
    {
        write_char(str[i]);
        i++;
    }
}

void clear_LCD()
{
    write_cmd(0x01);    // ��ʾ��0������ָ����0
}

