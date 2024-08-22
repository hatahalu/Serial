#include "DigitalInOut.h"
#include "UnbufferedSerial.h"
#include "mbed.h"

UnbufferedSerial ser(D5, D4, 9600);

int main()
{
    char a;
    while (true) {
        if(ser.readable()){
            ser.read(&a,sizeof(a));
            printf("REceived Value:%c\n",a);
        }
    }
}
