#include <stdio.h>
#include <sys/types.h> // for pid_t
#include <unistd.h> // for fork

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
            break;
        }
        
    }
}

/*
Output Sample:
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ gcc fork_Programming.c -o fork.out
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ ./fork.out
Hello World!!Parent Process 
child created with pid 17225 
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ Hello World!!Child Process 
child creation success full 0
*/