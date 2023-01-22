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
