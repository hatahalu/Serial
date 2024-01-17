#include "mbed.h"
#include "DigitalInOut.h"
#include "UnbufferedSerial.h"
UnbufferedSerial ser(D5, D4, 9600);

int main()
{
    char a = '1';
    while (true) {
        ser.write(&a, sizeof(a));
        wait_us(1000*1000);
    }
}
