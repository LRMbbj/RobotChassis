#ifndef __VOFA_H__
#define __VOFA_H__

#include "main.h"
#include <stdio.h>
#include <stdarg.h>

#define MAX_COUNT 5
#define tailBytes {0x00, 0x00, 0x80, 0x7f}

void VOFAInit(UART_HandleTypeDef* huart);
void VOFAprintf(const char* tag, const char* fmt, ...);
void VOFAJFSend(float data[], int num);
void VOFAFWSend(const char* tag, int arg_cnt, ...);
//void VOFALog();

#endif // !__VOFA_H__
