#include "reg51.h"

#define uchar unsigned char

// ��Ҫ���ĵĲ���
#define LCD_PORT P2 
sbit RS = P3^0;
sbit RW = P3^1;
sbit E  = P3^2;
// END