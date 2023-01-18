// CPP Program for FIFO IPC (Reader Process)
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{
    int fd;
    char myfifo[] = "/tmp/myfifo";
    char buf[80];

    // Open FIFO for Read only
    fd = open(myfifo, O_RDONLY);
    while (1)
    {
        // Read from FIFO
        read(fd, buf, sizeof(buf));
        // Print the read message
        cout << "User1: " << buf << endl;
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
        // Take an input arr2ing from user.
        // 80 is maximum length
        cin.getline(buf, 80);
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, buf, strlen(buf)+1);
        close(fd);
    }

    return 0;
}