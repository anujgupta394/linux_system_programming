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
            printf("child creation success full %d", pid);
            break;
        }
            
        case -1:
        {
            printf("fork failed %d", pid);
            break;
        }

        default:
        {
            printf("child created with pid %d", pid);
            break;
        }
        
    }
}

/*
Output Sample:
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ gcc fork_Programming.c -o fork.out
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ ls
a.out  fork.out  fork_Programming.c
anujgupta@anujgupta:~/linux_programming/linux_system_programming$ ./fork.out
Hello World!!child created with pid 15884anujgupta@anujgupta:~/linux_programming/linux_system_programming$ Hello World!!child creation success full 0
*/