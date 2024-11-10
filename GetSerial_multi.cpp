#include "mbed.h"

UnbufferedSerial uart_port(D5, D4, 9600); 

void receive_serial() {
    char rcvdata[128];
    int index = 0;
    char c;

    while (true) {
        if (uart_port.read(&c, 1) > 0) {
            if (c == '\n') {
                rcvdata[index] = '\0';
                break;
            } else {
                rcvdata[index++] = c;
            }
        }
    }

    printf("recv data : %s\n", rcvdata);
}

int main(void) {
    while(true){
        receive_serial();
    }
}
