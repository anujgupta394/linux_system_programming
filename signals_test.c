#include <stdio.h>
#include<stdlib.h> // for exit
#include <signal.h>
#include<sys/wait.h> // for wait
#include <unistd.h>    // for fork
//#include "tlpi_hdr.h"
static void
sigHandler(int sig)
{
    printf("Ouch!\n"); /* UNSAFE (see Section 21.1.2) */
}
int main(int argc, char *argv[])
{
    int j;
    if (signal(SIGTSTP, sigHandler) == SIG_ERR)
        printf("error");
    for (j = 0;; j++)
    {
        printf("%d\n", j);
        sleep(3); /* Loop slowly... */
    }
}