#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

// CRC-32 Implementation based on https://en.wikipedia.org/wiki/Cyclic_redundancy_check#CRC-32_algorithm
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
    // Open the FIFO for reading
    int fd = open("/tmp/myfifo", O_RDONLY);
    if (fd < 0) {
        cerr << "Error opening FIFO for reading" << endl;
        return 1;
    }

    // Read the message from the FIFO
    char buffer[1024];
    read(fd, buffer, 1024);
    close(fd);

    // Extract the message and the CRC-32 from the message
    string message = buffer;
    string crc = message.substr(message.find_last_of(" ") + 1);
    message = message.substr(0, message.find_last_of(" "));

    // Calculate the CRC-32 of the message
    unsigned int calculated_crc = crc32(message.c_str(), message.size());

    // Compare the CRC-32s
    if (to_string(calculated_crc) == crc) {
        cout << "Message received: " << message << endl;
    } else {
        cout << "Message received with errors: " << message << endl;
    }

    return 0;
}
