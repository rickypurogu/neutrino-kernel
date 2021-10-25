#include "serial.h"

unsigned short _PORT;

// *Initialize serial communication to specified port
// @param port serial port
void init_serial(unsigned short port) {
    _PORT = port;
    portByteOut(_PORT + 1, 0x00);    //Disable all interrupts
    portByteOut(_PORT + 3, 0x80);    //Enable DLAB
    portByteOut(_PORT + 0, 0x03);    //Set baud divisor to 3 (38400 baud)
    portByteOut(_PORT + 1, 0x00);    
    portByteOut(_PORT + 3, 0x03);    //Define 8 bits, no parity, one stop bit
    portByteOut(_PORT + 2, 0xc7);    //Enable FIFO   
    portByteOut(_PORT + 4, 0x0b);    //IRQs enabled, RTS/DSR set
}

// *Read from port defined in serial_init and return message char
// @return the value read from port defined in serial
char serial_read() {
    while (serial_received() == 0);
    return portByteIn(_PORT);
}

// *Write char c to port defined in serial_init
// @param c the character to be written
void serial_write(char c) {
    while (is_transmit_empty() == 0);
    portByteOut(_PORT, c);
}

// *Write a string to port defined in serial_init
// @param message the string to be written to the serial port
void serial_write_string(char* message) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        serial_write(message[i]);
    }
}

// === PRIVATE FUNCTIONS ========================

// *Return a value received form the port
// @return byte value read from port
int serial_received() {
    return portByteIn(_PORT + 5 ) & 1;
}

// *Return if the transmission buffer is empty
// @return true if the transmission buffer is empty, false otherwise
int is_transmit_empty() {
    return portByteIn(_PORT + 5) & 0x20;
}