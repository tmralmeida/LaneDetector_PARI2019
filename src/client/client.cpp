/**
 * @file cliente.cpp
 * @author Tiago Almeida, nº 77107 (tm.almeida@ua.pt)
 * @brief This Script includes the function main of the client side
 * @Final Version
 * @date 2019-01-27
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#define _MAIN_C_
#include "myclient.h"


/**
 * @brief  Function that makes the main fork of the program. 
 *
 *      
 *
 * @param  argc- number of arguments when the output is called 
 * @param  argv- the argument of the output 
 * @return  an integer
 */

int main(int argc, char *argv[])
{
    count_images=0;
    num_images=10;
    int pid = fork();
    int s_id;
    char string [20]={0};

    if (pid == -1)
    {
        printf("Could not fork(). Exiting\n");
        return -1;
    }

    if (pid == 0) /* The child */
    {
        MessageFromChild((char*)("I am the child\n"));
        ChildMain3(argc, argv);
        MessageFromChild((char*)("CHILD ended\n"));
    }
    else /* The parent */
    {
        MessageFromParent((char*)("I am the parent\n"));
        s_id = ParentMain3(argc,argv); //Get s_id from return value to know the id to destroy the shared mem
        if (s_id > 0)
            shmctl(s_id, IPC_RMID, NULL); //Allow elimination of shared memory

        MessageFromParent((char*)("PARENT ended\n"));
        
    }

    return 0;
}
