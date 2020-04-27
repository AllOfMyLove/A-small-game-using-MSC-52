#include "REG52.H"
void EX0_init()
{
    IT0 = 1;    // �½��ش���
    PX0 = 1;    // �����ȼ�
    EX0 = 1;    // �����ж�����
    EA = 1;     // ���ж�����
}

void EX1_init()
{
    IT1 = 1;
    PX1 = 0;
    EX1 = 1;
    EA = 1;
}

void TIM_0_init(void)
{
    // ��ʼ�� TMOD �Ĵ���
    // 50ms �ж�һ��
    TMOD = TMOD | 0x01;
    TH0 = (65536 - 50000) / 256;
    TL0 = (65536 - 50000) % 256;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void TIM_1_init(void)
{
    // ��ʼ�� TMOD �Ĵ���
    // ���������
    TMOD = TMOD | 0x20;
    TH1 = 239;
    TL1 = 239;
    ET1 = 0;    //���Ӷ̲�����
    TR1 = 1;    //��ʼ����
}