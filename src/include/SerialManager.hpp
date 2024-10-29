#ifndef SERIAL_MANAGER_HPP
#define SERIAL_MANAGER_HPP

#include "SerialPort.hpp"

//Class to manaage communication between two serial ports
class SerialManager {
public:
    SerialManager(const std::string& port1, const std::string& port2);

    bool configurePorts();
    void startCommunication();

private:
    SerialPort port1;
    SerialPort port2;
};

#endif // SERIAL_MANAGER_HPP
