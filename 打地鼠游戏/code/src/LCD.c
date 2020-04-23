#include "reg52.h"
#include "LCD.h"


void delay()
{
    uchar j=0,i=0;
    for(j=0;j<255;j++)
        for(i=0;i<4;i++);
}

void write_char(uchar dat)
{
    // ����ʱ��ͼ
    RS = 1;
    RW = 0;
    E  = 0;
    LCD_PORT = dat;
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
 * @param  addr: ��Ҫ��ʾ�׵�ַ
 * @param  *str: �ַ������׵�ַ
 */
void display_LCD(uchar addr,char *str)
{
    uchar i = 0;
    write_cmd(addr);
    while(str[i]!='\0')
    {
        write_char(str[i]);
        i++;
    }
}

#if 0
/**
 * @brief  ����Ļ����ʾ�����ַ�  
 * @param  addr: ��Ҫ��ʾ��ַ
 * @param  str: �ַ�
 */
void display_LCD_single(uchar addr ,char str)
{
    uchar i = 0;
    write_cmd(addr);
    write_char(str);
}
#endif

/* mode=0����ʾ���㣬ָ������
   mode=1: ��ָ������   */
void clear_LCD(bit mode)
{
    if(mode == 0)
        write_cmd(0x01);    // ��ʾ��0������ָ����0
    if(mode == 1)
        write_cmd(0x02);
}


char str[4];
char* uchar2string(uchar n)
{

    uchar *pStr;
    pStr = str;
    if (n > 99)
    {
        *pStr = n / 100 + '0';
        n %= 100;
        pStr += 1;
        *pStr = n / 10 + '0';
        n %= 10;
        pStr += 1;
        *pStr = n + '0';
    }
    if (n > 9)
    {
        *pStr = n / 10 + '0';
        n %= 10;
        pStr += 1;
        *pStr = n + '0';
    }
    if (n < 10)
    {
        *pStr = n + '0';
    }
    pStr += 1;
    *pStr = '\0';
    return str;
}