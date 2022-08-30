#include <stdio.h>
#include <sys/types.h> // for pid_t
#include<stdlib.h> // for exit
#include<sys/wait.h> // for wait
#include <unistd.h>    // for fork

void main()
{
    printf("Hello World!!");
    pid_t pid = fork();

    switch (pid)
    {
        case 0:
        {
            printf("Child Process \n");
            printf("child creation success full %d\n", pid);
            exit(3); // this exit status will be reflected in status of wait :
            break;
        }

        case -1:
        {
            printf("fork failed %d \n", pid);
            break;
        }

        default:
        {
            int status = 1;
            sleep(1);
            wait(&status); // status will not directly print status as status of exit
            //waitpid(pid, &status, 0); or this can be used
            printf("child exit status %d \n", WEXITSTATUS(status));
            printf("Parent Process \n");
            printf("child created with pid %d \n", pid);
            break;
    }
    }
}

/*
Output Sample:
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ gcc fork_with_wait_and_exit.c -o fork.out
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ ./fork.out
Hello World!!Child Process 
child creation success full 0
Hello World!!child exit status 3 
Parent Process 
child created with pid 21526 
*/