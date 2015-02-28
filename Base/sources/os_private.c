#include "os_private.h"

#include <stdio.h>
#include <windows.h>

/***********************************************************************************
	��ӡ����,Ϊ��CUnit�Ĵ�ӡ���ֿ�����������ɫ��ӡ����ɫ
***********************************************************************************/
int my_printf(char *format, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	int cnt;

	va_list list;
	va_start(list, format);
	cnt = vprintf(format, list);
	va_end(list);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	return cnt;
}

U64 get_systime_ms(void)
{
	return timeGetTime();
}
