/**
 *       @file  pcolor.c
 *      @brief  File to set printf() colors
 *
 * Not much on detailed description about pcolor
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================
 */

#include <stdio.h>
#include "myutils.h"

/**
 * @brief  Set the color of text that follows upon the next printf.
 *
 * @param  attr Type of attribute (RESET, BRIGHT, BLINK, etc...)
 * @param  fg Color of foreground
 * @param  bg Color of background
 * @return Nothing
 */
void textcolor1(int attr, int fg, int bg)
{
	printf("%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
}

/**
 * @brief  printf of an horizontal separator red line 
 *
 * @return Nothing
 */
void PrintRedLine1(void)
{
	int n;
	textcolor1(RESET, RED, WHITE);	//completar a função
	for(n=0; n< 40; n++) 
		printf("=");
	printf("\n");
}

/**
 * @brief  Reset color text
 *
 * @return Nothing
 */
void ResetTextColors1(void)
{
	textcolor1(RESET, BLACK, WHITE);	//completar a função
}

/**
 * @brief  Make somesort of highlight text
 *
 * @return Nothing
 */
void HighLightText1(void)
{
	textcolor1(RESET, BLUE, YELLOW);	//completar a função
}


