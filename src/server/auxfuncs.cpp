/**
 *      @file  auxfuncs.c
 *      @brief  auxiliary functions
 *
 * =====================================================================================
 */

#include "myserver.h"



void myerror(const char *msg)
{
	perror(msg);
	exit(1);
}

void ManageCTRL_C(int dummy)
{
	printf("User CTRL-C pressed. Closing server.\n");
	infinite_loopG=0;
}

