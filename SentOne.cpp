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
}#include "mbed.h"
#include "ICM20948.h"

// I2Cピンを定義
#define SDA_PIN PB_9  // D14
#define SCL_PIN PB_8  // D15

// シリアル通信の初期化（出力用）
UnbufferedSerial pc(USBTX, USBRX, 115200);  // TX, RX for L432KC

int main() {
    // ICM20948クラスのインスタンスを作成
    ICM20948 imu(SDA_PIN, SCL_PIN);

    // IMUを初期化
    imu.init(ACC_RATE_2g | ACC_LPF_136HZ, ACC_SMPLRT_100Hz, GYRO_RATE_250 | GYRO_LPF_17Hz, GYRO_SMPLRT_100Hz);

    // IMUが応答しているか確認
    int whoAmI = imu.whoAmI();
    if (whoAmI == 68) {
        printf("IMU接続成功!\n");
    } else {
        printf("IMU接続失敗。\n");
        return -1;
    }

    // センサーデータを連続して取得し表示
    while (true) {
        // 加速度およびジャイロデータを読み取る
        imu.getAccGyro();
        
        // 加速度値を取得
        float ax = imu.getAX();
        float ay = imu.getAY();
        float az = imu.getAZ();
        
        // ジャイロ値を取得
        float gx = imu.getGX();
        float gy = imu.getGY();
        float gz = imu.getGZ();
        
        // 温度値を取得
        int temperature = imu.getIMUTemp();

        // データをシリアルに出力
        printf("Accel X: %.2f m/s^2, Y: %.2f m/s^2, Z: %.2f m/s^2\n", ax * IMU_ONE_G, ay * IMU_ONE_G, az * IMU_ONE_G);
        printf("Gyro X: %.2f dps, Y: %.2f dps, Z: %.2f dps\n", gx, gy, gz);
        printf("Temperature: %d\n\n", temperature);

        // 読みやすさのための遅延
        ThisThread::sleep_for(500ms);
    }
}
