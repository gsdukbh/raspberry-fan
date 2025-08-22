#include <iostream>
#include <pigpio.h>
#include <fstream>
#include <unistd.h>
#include <math.h>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// 配置结构体
struct Config {
    int fan_gpio_pin = 14;      // 默认GPIO 14
    int max_temp = 80;          // 默认最高温度 80°C
    int min_temp = 70;          // 默认最低温度 70°C
    int check_interval = 10;    // 默认检测间隔 10秒
    bool debug_mode = true;     // 默认启用调试模式
};

// 读取配置文件
Config loadConfig(const string& configFile) {
    Config config;
    ifstream file(configFile);
    
    if (!file.is_open()) {
        cerr << "Warning: 无法打开配置文件 '" << configFile << "'，使用默认配置" << endl;
        return config;
    }
    
    string line;
    while (getline(file, line)) {
        // 跳过空行和注释行
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // 查找等号分割键值对
        size_t pos = line.find('=');
        if (pos == string::npos) {
            continue;
        }
        
        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);
        
        // 解析配置项
        if (key == "fan_gpio_pin") {
            config.fan_gpio_pin = stoi(value);
        } else if (key == "max_temp") {
            config.max_temp = stoi(value);
        } else if (key == "min_temp") {
            config.min_temp = stoi(value);
        } else if (key == "check_interval") {
            config.check_interval = stoi(value);
        } else if (key == "debug_mode") {
            config.debug_mode = (stoi(value) == 1);
        }
    }
    
    file.close();
    return config;
}

// 读取CPU温度
int readCPUTemperature() {
    char data[10];
    ifstream infile("/sys/class/thermal/thermal_zone0/temp");
    
    if (!infile.is_open()) {
        cerr << "Error: 无法读取CPU温度" << endl;
        return -1;
    }
    
    infile >> data;
    infile.close();
    
    return atoi(data) / 1000;  // 转换为摄氏度
}

int main() {
    // 加载配置
    Config config = loadConfig("config.txt");
    gpioCfgSocketPort(10003);// 使用10003 作为默认端口
    if (config.debug_mode) {
        cout << "配置加载完成:" << endl;
        cout << "  GPIO引脚: " << config.fan_gpio_pin << endl;
        cout << "  最高温度: " << config.max_temp << "°C" << endl;
        cout << "  最低温度: " << config.min_temp << "°C" << endl;
        cout << "  检测间隔: " << config.check_interval << "秒" << endl;
        cout << "  调试模式: " << (config.debug_mode ? "启用" : "禁用") << endl;
        cout << "========================" << endl;
    }
    
    // 初始化GPIO
    if (gpioInitialise() < 0) {
        cerr << "Error: pigpio 初始化失败" << endl;
        return 1;
    }
    
    // 设置风扇GPIO为输出模式
    gpioSetMode(config.fan_gpio_pin, PI_OUTPUT);
    
    if (config.debug_mode) {
        cout << "GPIO " << config.fan_gpio_pin << " 已设置为输出模式" << endl;
    }
    
    bool fanRunning = false;  // 记录风扇当前状态
    
    while (true) {
        // 读取CPU温度
        int temp = readCPUTemperature();
        
        if (temp == -1) {
            cerr << "Error: 温度读取失败，跳过本次检测" << endl;
            sleep(config.check_interval);
            continue;
        }
        
        if (config.debug_mode) {
            cout << "CPU温度: " << temp << "°C";
        }
        
        // 温度控制逻辑
        if (temp > config.max_temp && !fanRunning) {
            // 温度过高，开启风扇
            gpioWrite(config.fan_gpio_pin, 1);
            fanRunning = true;
            if (config.debug_mode) {
                cout << " -> 温度超过 " << config.max_temp << "°C，开启风扇" << endl;
            }
        } else if (temp <= config.min_temp && fanRunning) {
            // 温度降低，关闭风扇
            gpioWrite(config.fan_gpio_pin, 0);
            fanRunning = false;
            if (config.debug_mode) {
                cout << " -> 温度降至 " << config.min_temp << "°C以下，关闭风扇" << endl;
            }
        } else {
            // 温度在正常范围内，保持当前状态
            if (config.debug_mode) {
                cout << " -> 风扇状态: " << (fanRunning ? "运行中" : "已停止") << endl;
            }
        }
        
        // 等待指定间隔时间
        if (config.debug_mode) {
            cout << "等待 " << config.check_interval << " 秒..." << endl;
            cout << "========================" << endl;
        }
        
        sleep(config.check_interval);
    }
    
    // 程序退出时清理GPIO资源
    gpioTerminate();
    return 0;
}
