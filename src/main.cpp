#include "include/SerialManager.hpp"
#include <iostream>

//Main function to initialize and start serial communication
int main(int argc, char *argv[]) {
    
    //check if two serial port names are provided
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <serial_port_1> <serial_port_2>" << std::endl;
        return 1;
    }
    //create an instante of SerialManager with the given serial ports
    SerialManager manager(argv[1], argv[2]);

    if (!manager.configurePorts()) {
        std::cerr << "Failed to configure one or both serial ports." << std::endl;
        return 1;
    }
    //start communication between the two serial ports
    manager.startCommunication();

    return 0;
}
