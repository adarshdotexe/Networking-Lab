#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

unsigned int crc32(const char *buf, size_t size) {
    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < size; i++) {
        crc ^= buf[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = (crc >> 1);
            }
        }
    }
    return crc ^ 0xFFFFFFFF;
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
