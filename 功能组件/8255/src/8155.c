#include "8155.H"

/**
 * @brief  ����8155�Ĺ���״̬
 * @note   
 * @param  command_2_8155: ����8155����״̬�Ĳ���
 * @retval None
 */
void Set8155(uchar command_2_8155)
{
    CMD_8155 = command_2_8155;
}

/**
 * @brief  ������д��PA,PB,PC��
 * @note   
 * @param  white_line: Ҫд�������
 * @retval None
 */
void WritePA(uchar white_line)
{
    PA_8155 = white_line;
}

void WritePB(uchar white_line)
{
    PB_8155 = white_line;
}

void WritePC(uchar white_line)
{
    PC_8155 = white_line;
}


