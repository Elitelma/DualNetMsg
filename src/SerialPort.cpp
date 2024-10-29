#include "include/SerialPort.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <cerrno>

SerialPort::SerialPort(const std::string& portName) : portName(portName), fd(-1) {}

SerialPort::~SerialPort() {
    close(fd);
}

//configure the serial ports settings
bool SerialPort::configure() {
    fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        std::cerr << "Error opening " << portName << ": " << strerror(errno) << std::endl;
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error getting attributes for " << portName << ": " << strerror(errno) << std::endl;
        close(fd);
        return false;
    }

    //set baud rates for the ports
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    //configure serial port settings
    tty.c_cflag |= (CLOCAL | CREAD); //Enaable receiver and set local mode
    tty.c_cflag &= ~CSIZE;           // Clear character size mask
    tty.c_cflag |= CS8;              // Set 8 data bits
    tty.c_cflag &= ~PARENB;          // No parity bit
    tty.c_cflag &= ~CSTOPB;          // 1 stopo bit
    tty.c_cflag &= ~CRTSCTS;         // Disable hardware flow control

    //configure local modes
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Disable software flow
    tty.c_oflag &= ~OPOST;                          // Raw output

    //set new attibutes for the serial port
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting attributes for " << portName << ": " << strerror(errno) << std::endl;
        close(fd);
        return false;
    }

    return true;
}


void SerialPort::sendMessage(const std::string& message) {
    if (write(fd, message.c_str(), message.size()) < 0) {
        std::cerr << "Error sending message on " << portName << ": " << strerror(errno) << std::endl;
    }
}

void SerialPort::receiveMessage() {
    char buf[256];
    int n = read(fd, buf, sizeof(buf));
    if (n < 0) {
        std::cerr << "Error reading message from " << portName << ": " << strerror(errno) << std::endl;
    } else if (n > 0) {
        buf[n] = '\0';  // Null-terminate the received data
        std::cout << "Received by " << portName << " : " << buf << std::endl;
    }
}

void SerialPort::startReading() {
    readingThread = std::thread(&SerialPort::readLoop, this);
}

void SerialPort::stopReading() {
    if (readingThread.joinable()) {
        readingThread.join();
    }
}

void SerialPort::readLoop() {
    while (true) {
        receiveMessage();
        usleep(100000);  // Sleep for 100ms
    }
}
