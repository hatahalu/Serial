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
}#include "mbed.h"

// I2Cインスタンスの作成
I2C i2c(PB_9, PB_8); // SDA, SCLピンを指定（ボードによって異なる）

// ICM-20948のI2Cアドレス
#define ICM20948_ADDRESS 0x68 << 1

// レジスタの定義
#define WHO_AM_I_REG 0x00
#define ACCEL_XOUT_H 0x2D

// 初期化関数
bool initICM20948() {
    char who_am_i[1];
    who_am_i[0] = WHO_AM_I_REG;
    
    // WHO_AM_Iレジスタを読む
    if (i2c.write(ICM20948_ADDRESS, who_am_i, 1) != 0) return false;
    if (i2c.read(ICM20948_ADDRESS, who_am_i, 1) != 0) return false;
    
    return (who_am_i[0] == 0xEA); // ICM-20948のWHO_AM_I値が0xEA
}

// 加速度データ取得関数
void readAccelData(int16_t *accelData) {
    char data[6];
    data[0] = ACCEL_XOUT_H;
    
    i2c.write(ICM20948_ADDRESS, data, 1); // データ読み取り開始
    i2c.read(ICM20948_ADDRESS, data, 6);  // 加速度データを取得
    
    // X, Y, Z軸のデータを取得
    accelData[0] = (data[0] << 8) | data[1];
    accelData[1] = (data[2] << 8) | data[3];
    accelData[2] = (data[4] << 8) | data[5];
}

int main() {
    printf("ICM-20948 Test\n");

    // ICM-20948の初期化
    if (!initICM20948()) {
        printf("ICM-20948 not detected!\n");
        return 1;
    }

    printf("ICM-20948 detected!\n");

    int16_t accelData[3];
    
    while (true) {
        // 加速度データを読み取る
        readAccelData(accelData);
        
        // 加速度データを表示
        printf("Accel X: %d, Y: %d, Z: %d\n", accelData[0], accelData[1], accelData[2]);
        
        wait(0.5); // 0.5秒待機
    }
}
