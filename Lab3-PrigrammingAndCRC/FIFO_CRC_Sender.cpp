#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

unsigned int crc32(const char *data, size_t length) {
    static unsigned int table[256];
    static bool initialized = false;
    if (!initialized) {
        // Compute the table of CRCs of all 8-bit messages.
        for (unsigned int i = 0; i < 256; i++) {
            unsigned int c = i;
            for (unsigned int k = 0; k < 8; k++) {
                if (c & 1) {
                    c = 0xedb88320 ^ (c >> 1);
                } else {
                    c = c >> 1;
                }
            }
            table[i] = c;
        }
        initialized = true;
    }

    // Compute the CRC of the data using the table.
    unsigned int c = 0xffffffff;
    for (size_t i = 0; i < length; i++) {
        c = table[(c ^ data[i]) & 0xff] ^ (c >> 8);
    }
    return c ^ 0xffffffff;
}


int main() {
    string message;
    cout << "Enter message to send: ";
    getline(cin, message);

    // Append the CRC-32 of the message to the message itself
    unsigned int crc = crc32(message.c_str(), message.size());
    message += " " + to_string(crc);

    // Open the FIFO for writing
    int fd = open("/tmp/myfifo", O_WRONLY);
    if (fd < 0) {
        cerr << "Error opening FIFO for writing" << endl;
        return 1;
    }

    // Write the message to the FIFO
    write(fd, message.c_str(), message.size());
    close(fd);

    cout << "Message sent: " << message << endl;
    return 0;
}
