#ifndef _OS_PRIVATE_H_
#define _OS_PRIVATE_H_

typedef unsigned long	U64;

int my_printf(char *format, ...);

U64 get_systime_ms(void);

#endif