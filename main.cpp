#include <iostream>
#include <wiringPi.h>
#include <fstream>
#include <unistd.h>
#include <math.h>

using namespace std;

int main() {
    wiringPiSetup();
    int fan = 15;
    pinMode(fan, OUTPUT);
    while (TRUE) {
        char data[10];
        ifstream infile;
        infile.open("/sys/class/thermal/thermal_zone0/temp");
        infile >> data;
        infile.close();
        cout << "cpu 温度: " << data << endl;
        int temp = atoi(data) / 1000;
        int maxTemp = 80;
        int minTemp = 60;
        if (temp > maxTemp) {
            cout << "--温度大于 " << maxTemp << " 开启疯扇---" << endl;
            digitalWrite(fan, HIGH);
        }
        if (temp <= minTemp) {
            cout << "--温度小于" << minTemp << " 关闭疯扇---" << endl;
            digitalWrite(fan, LOW);
        }
        cout << "线程停顿-10s" << endl;
        sleep(5);
    }
    return 0;
}
