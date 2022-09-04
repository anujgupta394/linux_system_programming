#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFSIZE 1024
void main()
{
    // first arg is path name second is flags - wants to open in read or write or both but
    // third is mode(chmod- permission)
    int fin, fout;
    int count = 0;
    char buffer[BUFFSIZE];
    if ((fin = open("read_from_file", O_RDONLY, 0644)) < 0)
    {
        printf("error fin");
    }

    if ((fout = open("write_to_file", O_WRONLY | O_CREAT, 0644)) < 0)
    {
        printf("error fout");
    }

    // buffer size is the size which will store the data from file and write
    // the data to another file
    // in while loop read will read data of BUFFSIZE first then it will read the same
    //  as count(ie no of bytes read) again in second iteration of while
    //  will read another BUFFSIZE or if data is less than BUFFSIZE it will read that no
    // of bytes and return the same
    //  for example if BUFFSIZE is 1024. and no of byte in file are 1030
    // then first read will read 1024 and return 1024. then read will read remaining 6
    // bytes and return 6
    // we can make buffer big and make BUFFSIZE less but oppposite will cause issues
    while ((count = read(fin, buffer, BUFFSIZE)) > 0)
    {
        printf("reading %d", count);
        write(fout, buffer, count);
    }
    close(fin);
    close(fout);
}