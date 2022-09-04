#include <stdio.h>
#include <stdlib.h> // for exit
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for wait
#include <string.h> // for strsignal
/* In this program fork creates child process then
child sets its handler and then gives chance to parent by adding sleep and
parent sets its handler and then sends signal and child receives it and then gives
chance to child to fire signal then parents handles it and print handler's message
*/

static void parentHandler(int sig)
{
    printf("parent Handler");
}

static void childHandler(int sig)
{
    printf("child Handler");
}

void main()
{
    pid_t pid = fork();

    switch (pid)
    {
        case 0:
        {
            printf("Child Process %d\n", getpid());
            printf("child creation success full %d\n", pid);
            pause();
            sleep(100);
            break;
        }

        case -1:
        {
            printf("fork failed %d \n", pid);
            break;
        }

        default:
        {
            int status = 0;
            printf("Parent Process \n");
            printf("child created with pid %d \n", pid);
            wait(&status);
            if (WIFSIGNALED(status))
            {
                printf("signal which terminated %s", strsignal(WTERMSIG(status))); // can use this way to print info
                psignal(WTERMSIG(status), "terminated by signal"); // or this way
            }
            break;
        }
    }
}

/*********** Terminating child process using signals sets the wait status accordingly***********************
Here create child and parent process using fork
print the process IDs of child and parent
add a wait call in parent which will wait untill child process is successfully finished
or child process is terminated by any signal
in both cases we get the status information in the status of wait
try it using kill -TERM or we can use other signals eg ABORT ie removing SIG
from actual name and add - before it
process_id_no_of_child
get process_id_no from printed logs
then in parent we get true for WIFSIGNALED status of wait tells child was terminated
by signal and WTERMSIG(status) tells the integer value of the signal which terminated
child
from second terminal eg.

anujgupta@anujgupta:~/linux_programming/linux_system_programming$ kill -ABRT 6274
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ kill -TERM 6420
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ kill -ABRT 6999
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ kill -HUP 7256
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ kill -FPE 7498
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ 

in first terminal output of last kill command
./read
Parent Process 
child created with pid 7498 
Child Process 7498
child creation success full 0
terminated by signal: Floating point exception
signal which terminated Floating point exception
*/