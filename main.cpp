#include <iostream>
#include <pigpio.h>
#include <fstream>
#include <unistd.h>
#include <math.h>

using namespace std;

int main() {
     // 禁止自动绑定端口
    gpioCfgSetSocketPort(0);
    while (true) {
        if (gpioInitialise() < 0) {
            std::cerr << "pigpio initialization failed." << std::endl;
            return 1;
        }
        int fan = 14;
        gpioSetMode(fan,PI_OUTPUT);
        char data[10];
        ifstream infile;
        infile.open("/sys/class/thermal/thermal_zone0/temp");
        infile >> data;
        infile.close();
        cout << "cpu 温度: " << data << endl;
        int temp = atoi(data) / 1000;
        int maxTemp = 80;
        int minTemp = 70;
        if (temp > maxTemp) {
            cout << "--温度大于 " << maxTemp << " 开启疯扇---" << endl;
            gpioWrite(fan,1);
        }
        if (temp <= minTemp) {
            cout << "--温度小于" << minTemp << " 关闭疯扇---" << endl;
            gpioWrite(fan,0);
        }
        cout << "线程停顿-10s " << endl;
        gpioTerminate();
        sleep(10);
    }
    return 0;
}
