#include "overflow_checker.h"

#define TRUE 1
#define FALSE 0

int chk_overflow(unsigned long current_value, unsigned long previous_value)
{
	if(current_value < previous_value)
		return TRUE;
	else
		return FALSE;
}
