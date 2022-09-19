#include "vofa.h"

UART_HandleTypeDef* vofaphuart;


char *Float2String(float value)
{
    char* str = (char*)malloc(10);
    int Head = (int)value;
    int Point = (int)((value - Head) * 100000.0);
    sprintf(str, "%d.%d", Head, Point);

    return str;
}
int _write(int fd, char *ptr, int len)  
{
    HAL_UART_Transmit(vofaphuart, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}

void VOFAprintf(const char* tag, const char* fmt, ...)
{
    uint8_t str[50];
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char*)str, fmt, ap);
    va_end(ap);
    printf("[\t%s]:%s\n",tag ,str);
    
}

void VOFAInit(UART_HandleTypeDef* huart)
{
    vofaphuart = huart;
}

void VOFAJFSend(float data[], int num) //unfinished
{

    //    HAL_UART_Transmit_DMA(vofaphuart, (uint8_t*)data, sizeof(float) * num);
    for(uint8_t i = 0 ; i < num ; i++)
    {
        HAL_UART_Transmit(vofaphuart, (uint8_t*)&(data[i]), sizeof(float), 100);
    }
    HAL_UART_Transmit(vofaphuart, (uint8_t*)"\x00\x00\x80\x7f", 4, 100);
}

void VOFAFWSend(const char* tag, int arg_cnt, ...)
{
    if (tag != NULL) printf("%s:", tag);
    
    int32_t val;
    
    va_list ap;
    va_start(ap, arg_cnt);
    val = va_arg(ap, int32_t);
//    printf("%s", Float2String(val));
    printf("%d", val);
    
    for (uint8_t i = 1; i < arg_cnt; i++)
    {
        val = va_arg(ap, int);
//        printf(",%s", Float2String(val));
        printf(",%d", val);
    }
    va_end(ap);
    printf("\n");
}
