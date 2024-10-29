#include "include/SerialManager.hpp"
#include <iostream>

SerialManager::SerialManager(const std::string& port1, const std::string& port2)
    : port1(port1), port2(port2) {}

bool SerialManager::configurePorts() {
    return port1.configure() && port2.configure();
}

void SerialManager::startCommunication() {
    port1.startReading();
    port2.startReading();

    std::string input;
    while (true) {
        std::cout << "Enter message to send (Ctrl+C to exit): ";
        std::getline(std::cin, input);

        std::cout << "Sending message to port: " << port1.getPortName() << std::endl;
        port1.sendMessage(input);
        std::cout << "Sending message to port: " << port2.getPortName() << std::endl;
        port2.sendMessage(input);
        std::cout << std::endl;
    }
}
