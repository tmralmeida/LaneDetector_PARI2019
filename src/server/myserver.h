/**
 *       @file  myserver.h
 *      @brief  
 *
 * Detailed description starts here.
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =====================================================================================
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>




#ifdef _MAIN_C_
	int infinite_loopG;
	int count_images;

#else
	extern int infinite_loopG;
	extern int count_images;
#endif

typedef struct { int hora, minutos;} tempo;

#include "prototypes.h"

