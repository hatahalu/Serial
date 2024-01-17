#include "mbed.h"
#include "DigitalInOut.h"
#include "UnbufferedSerial.h"
UnbufferedSerial ser(D5, D4, 9600);

int main()
{
    int byte = 1;
    while (true) {
        ser.write(&byte, 1);
        wait_us(1000*1000);
    }
}
