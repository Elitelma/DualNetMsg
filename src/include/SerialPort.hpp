#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <string>
#include <thread>

// SerialPort  class to abstract serial communication

class SerialPort {
public:
    SerialPort(const std::string& portName);
    ~SerialPort();

    bool configure();
    void sendMessage(const std::string& message);
    void receiveMessage();
    void startReading();
    void stopReading();

    std::string getPortName() const { return portName; }

private:
    std::string portName;
    int fd;
    std::thread readingThread;

    void readLoop();
};

#endif // SERIAL_PORT_HPP
