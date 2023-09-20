#include "DigitalInOut.h"
#include "UnbufferedSerial.h"
#include "mbed.h"

UnbufferedSerial ser(D5, D4, 9600);

int main()
{
    char byte;
    while (true) {
        ser.read(&byte, 1);
        printf("%c", byte);
    }
}

