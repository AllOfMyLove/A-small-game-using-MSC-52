#include"stdlib.h"

#define uchar unsigned char
#include "reg52.h"

// TODO ռ�ÿռ�ϴ󣬴��Ż�

void init_random(unsigned char seed)
{
    srand(seed);
}

uchar random(void)
{
    return rand()%15;
}

