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
  while (1) {
    char data[10];
    ifstream infile;
    infile.open("/sys/class/thermal/thermal_zone0/temp");
    infile >> data;
    infile.close();
    cout << "cpu 温度: " << data << endl;
    int temp = atoi(data) / 1000;
    if (temp > 60) {
      cout << "--温度大于60 开启疯扇---" << endl;
      digitalWrite(fan, HIGH);
    }
    if (temp <= 55) {
      cout << "--温度小于55 关闭疯扇---" << endl;
      digitalWrite(fan, LOW);
    }
    cout << "线程停顿-10s" << endl;
    sleep(10);
  }
  return 0;
}
