#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define BUFFSIZE 1024
/***************************************************
 * program to read and write from and to terminal
 * using read and write functions and
 * file descriptor 0 as stdin
 * and 1 as stdout
 * 
 * 3 specidfic datastreams - stdin stdout stderr
echo $? gives status or return code of previous command - 0 means success
 * *************************************************/
void main()
{
    int fin = 0;  // for stdin
    int fout = 1; // for stdout
    int count = 0;
    char buffer[BUFFSIZE];

    // read will take input from user (keyboard)
    // write will print it to terminal
    char * msg = "Enter the string\n";
    int size = strlen(msg);
    char * returnMsg = "You Entered: \n";
    int sizeReturnMsg = strlen(returnMsg);
    write(fout, msg, size);
    while ((count = read(fin, buffer, BUFFSIZE)) > 0)
    {
        write(fout, returnMsg, sizeReturnMsg);
        write(fout, buffer, count);      
        write(fout, msg, size);
    }
    close(fin);
    close(fout);
}