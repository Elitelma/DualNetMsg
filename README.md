# DualNetMsg

**DualNetMsg** is a command-line tool (CLI) written in C++ for sending and receiving messages through two serial ports at the same time. This software allows real-time monitoring and control of devices connected on both ports, making it ideal for applications that need simultaneous communication across two networks.

## Features

- **Serial Port Configuration**: Sets up communication parameters like baud rate, data bits, parity, and flow control.
- **Message Sending and Receiving**: Sends messages to both serial ports and displays received messages.
- **Asynchronous Reading**: Supports continuous reading with a dedicated thread for each port, enabling real-time data transfer.
- **Command-Line Interface (CLI)**: Allows users to interact directly by sending messages and viewing received ones.

## Project Structure

- **SerialPort**: Class that manages low-level operations to configure and communicate with a serial port.
- **SerialManager**: Class responsible for coordinating message communication between the two serial ports, sending messages, and starting the data-reading process.

## Requirements

- **Operating System**: Linux (or Linux-compatible environments, like WSL on Windows)
- **C++ Compiler**: Requires support for C++11 or later

## How to Build

In the terminal, go to the project directory and run the following commands:

```bash
mkdir build
cd build
cmake ..
make

This will create the DualNetMsg executable.

## Usage
To run the program, use the following command:

```bash
./DualNetMsg <serial_port_1> <serial_port_2>

The program will then ask you to enter messages to send to both ports. Received messages will be shown in the terminal.
