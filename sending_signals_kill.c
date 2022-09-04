#include <stdio.h>
#include <stdlib.h> // for exit
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> // for pid_t
#include <sys/wait.h>  // for wait

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
           
            printf("Child Process \n");
            printf("child creation success full %d\n", pid);
            if (signal(SIGUSR2, childHandler) == SIG_ERR)
            {
                printf("error handler child");
            }
             sleep(5);
             //get parent pid using getppid()
            int status = kill(getppid(), SIGUSR1); //SIGUSR1 and SIGUSR2 signals are reserved for user use
            sleep(1);
            break;
        }

        case -1:
        {
            printf("fork failed %d \n", pid);
            break;
        }

        default:
        {
            printf("Parent Process \n");
            printf("child created with pid %d \n", pid);
            if (signal(SIGUSR1, parentHandler) == SIG_ERR)
            {
                printf("error handler parent");
            }
            sleep(1);
            pause();
            int status = kill(pid, SIGUSR2);

            break;
        }
    }

    
}

/*
Sample output:
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ gcc sending_signals_kill.c -o send
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ ./send
Parent Process 
child created with pid 6586 
Child Process 
child creation success full 0
parent Handleranujgupta@anujgupta:~/linux_programming/linux_system_programming$ child Handler
*/