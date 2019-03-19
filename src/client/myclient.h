/**
 * @file myclient.h
 * @author Tiago Almeida, nº 77107 (tm.almeida@ua.pt)
 * @brief 
 * @version 0.1
 * @date 2018-12-12
 * 
 * @copyright Copyright (c) 2018
 * 
 */

/**
 *      @file  myclient.h
 *      @brief  header file for a more advanced TCP client
 *
 * Detailed description starts here.
 *
 *     @author  aaa aaa, aaaaaa@ua.pt
 *
 * =====================================================================================
 */

#ifndef _MYCLIENT_H_
#define _MYCLIENT_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8

/**
* @Colors
*/

#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define GRAY            7
#define WHITE           8

void textcolor(int attr, int fg, int bg);
void PrintRedLine(void);
void ResetTextColors(void);
void HighLightText(void);

#ifdef _MAIN_C_
 	int pid_childG=0;
	GtkBuilder *builderG;
	IplImage *dst_imageG=NULL;
	IplImage *src_imageG=NULL;
	struct Memory* data;
	int count_images;
	int num_images;

#else
    	extern int pid_childG;
	extern GtkBuilder *builderG;
	extern IplImage *dst_imageG, *src_imageG;
	extern struct Memory* data;
	extern int count_images;
	extern int num_images;



#endif


//...
#define SHM_SIZE 128       /**< 128 bytes for shared memory */
#define PARENTDELAY 300000 /**<parent period in us*/
#define CHILDDELAY 900000  /**<child delay in us*/

#define MAXCHARS 75 //just a large buffer for data chunks
#define  NOT_READY  -1
#define  FILLED     0
#define  TAKEN      1

typedef enum {NOTAVAILABLE=0, PORTCLOSED, PORTOPEN} srv_status;
 
struct Memory
{
    int  status;
    int  exist_ligacao;
    int  pedid_ligacao;
    char data_filho[50];
    char data_pai[50];
    unsigned char data_pai_imgdata[3932170];
    int height = 0;
    int width = 0;
};

#endif
#include "prototypes.h"
