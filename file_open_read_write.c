#include <sys/stat.h>
#include <fcntl.h>

/*The open() system call either opens an existing file or creates and opens a new file.*/

/* **********************OPEN************************************
int open(const char *pathname, int flags, ... mode_t mode );
Returns file descriptor on success, or –1 on error
If pathname is a symbolic
link, it is dereferenced. */

/*The file to be opened is identified by the pathname argument. If pathname is a symbolic
link, it is dereferenced. On success, open() returns a file descriptor that is used
to refer to the file in subsequent system calls. If an error occurs, open() returns –1
and errno is set accordingly.*/

/* mode argumnet has multiple modes
3 of them are access mode O_RDWR, O_RDONLY, O_WRONLY
O_RDWR is not equivalent toO_RDONLY | O_WRONLY; the latter combination is a logical error.*/

/*****************************************READ*********************************
The read() system call reads data from the open file referred to by the descriptor fd.
O_EXCL
This flag is used in conjunction with O_CREAT to indicate that if the file
already exists, it should not be opened; instead, open() should fail, with
errno set to EEXIST. In other words, this flag allows the caller to ensure that it
is the process creating the file. The check for existence and the creation of
the file are performed atomically. We discuss the concept of atomicity in
Section 5.1. When both O_CREAT and O_EXCL are specified in flags, open() fails
(with the error EEXIST) if pathname is a symbolic link. SUSv3 requires this
behavior so that a privileged application can create a file in a known location
without there being a possibility that a symbolic link would cause the
file to be created in a different location (e.g., a system directory), which
would have security implications.*/

/* #include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count);
Returns number of bytes read, 0 on EOF, or –1 on error
The count argument specifies the maximum number of bytes to read. (The size_t
data type is an unsigned integer type.) The buffer argument supplies the address of
the memory buffer into which the input data is to be placed. This buffer must be at
least count bytes long.
A successful call to read() returns the number of bytes actually read, or 0 if end-offile
is encountered. On error, the usual –1 is returned. The ssize_t data type is a
signed integer type used to hold a byte count or a –1 error indication.
*/

/**************************WRITE*************************************
The write() system call writes data to an open file.
#include <unistd.h>
ssize_t write(int fd, void *buffer, size_t count);
Returns number of bytes written, or –1 on error
The arguments to write() are similar to those for read(): buffer is the address of the
data to be written; count is the number of bytes to write from buffer; and fd is a file
descriptor referring to the file to which data is to be written.
On success, write() returns the number of bytes actually written; this may be
less than count.
*/

/**********************************CLOSE********************************
The close() system call closes an open file descriptor, freeing it for subsequent reuse
by the process. When a process terminates, all of its open file descriptors are automatically
closed.
#include <unistd.h>
ssize_t write(int fd, void *buffer, size_t count);
Returns number of bytes written, or –1 on
#include <unistd.h>
int close(int fd);
Returns 0 on success, or –1 on error
*/

/********************************LSEEK*********************************
For each open file, the kernel records a file offset, sometimes also called the readwrite
offset or pointer. This is the location in the file at which the next read() or write()
will commence. The file offset is expressed as an ordinal byte position relative to
the start of the file. "The first byte of the file is at offset 0".
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
Returns new file offset if successful, or –1 on error
The offset argument specifies a value in bytes. (The off_t data type is a signed integer
type specified by SUSv3.) The whence argument indicates the base point from which
offset is to be interpreted, and is one of the following values:
SEEK_SET
The file offset is set offset bytes from the beginning of the file.
SEEK_CUR
The file offset is adjusted by offset bytes relative to the current file offset.
SEEK_END
The file offset is set to the size of the file plus offset. In other words, offset is
interpreted with respect to the next byte after the last byte of the file.
Figure 4-1 shows how the whence argument is interpreted.
lseek(fd, 0, SEEK_SET); Start of file
lseek(fd, 0, SEEK_END);  Next byte after the end of the file
lseek(fd, -1, SEEK_END);  Last byte of file
lseek(fd, -10, SEEK_CUR); Ten bytes prior to current location

Appending data to a file
A second example of the need for atomicity is when we have multiple processes
appending data to the same file (e.g., a global log file). For this purpose, we might
consider using a piece of code such as the following in each of our writers:
if (lseek(fd, 0, SEEK_END) == -1)
errExit("lseek");
if (write(fd, buf, len) != len)
fatal("Partial/failed write");
lseek(fd, 10000, SEEK_END);  10001 bytes past last byte of file


*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
    int fd = open("Hello_World.txt", O_RDWR | O_SYNC | O_CREAT);
    if (fd == -1)
    {
        printf("error opening file\n");
    }

    int flags = fcntl(fd, F_GETFL);       // third argiment is used to set flags might be using F_SETFL or others,
                                          // for reading flags no purpose, reads using fd file descriptor
    int accessMode = (flags & O_ACCMODE); // to check for read or write or readwrite
    // there are three access mode out of many modes
    // read only // write only // read_write
    // in actual flag there can be only one bit set either for read/write/readwrite
    //so O_ACCMODE will have these three bit set only and when we do & operation the set bit of flag will &
    // with set bit of O_ACCMODE others will be 0
    // flags 01011000 => this is for example only dont know which bits are for read/write/readwrite.
    //suppose 4th bit from right is for readwrite
    // now ACCMODE will have 3 bits set 10001111
    //01011000 in this either of the set bit from ACCMODE can be set means there will be only one access mode
    //10001100
    //& will be 00001000 which has set bit of read write
    
    if (flags == -1)
    {
        printf("error fetching access Mode\n");
    }

    if (accessMode == O_RDWR)
    {
        printf("read_write Mode\n");
    }

    int isSyncMode = (flags & O_SYNC);

    if (isSyncMode)
    {
        printf("Sync Mode\n");
    }

    close(fd);
}