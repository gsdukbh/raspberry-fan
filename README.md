# raspberry-fan 

## Description

这是一个智能控制风扇的小工具，支持通过配置文件自定义参数。

## 新功能特性

### 配置文件支持
- 使用 `config.txt` 配置文件自定义所有参数
- 支持GPIO引脚配置
- 支持温度阈值配置
- 支持检测间隔配置
- 支持调试模式开关

### 改进的功能
- 更好的错误处理机制
- 避免频繁的GPIO初始化
- 风扇状态跟踪，避免重复操作
- 详细的调试信息输出

## 配置文件说明

配置文件 `config.txt` 支持以下参数：

```
# GPIO引脚配置 (默认: 14)
fan_gpio_pin=14

# 最高温度阈值，超过此温度启动风扇 (默认: 80°C)
max_temp=80

# 最低温度阈值，低于此温度停止风扇 (默认: 70°C) 
min_temp=70

# 温度检测间隔时间，单位秒 (默认: 10秒)
check_interval=10

# 调试模式开关 (1=启用, 0=禁用, 默认: 1)
debug_mode=1
```

## Usage

1. 编辑 `config.txt` 文件配置你的参数
2. 运行程序

### 手动运行
```bash
# 编译
mkdir build && cd build
cmake .. && make

# 运行 (需要root权限)
sudo ./raspberry_fan
```

### 系统服务安装
```bash
chmod +x install.sh && sudo ./install.sh
```

## Install

```bash
git clone https://github.com/gsdukbh/raspberry-fan.git
cd raspberry-fan
chmod +x install.sh && sudo ./install.sh
```

安装脚本会自动：
- 安装必要的依赖
- 编译程序
- 安装到系统目录
- 配置为系统服务
- 设置开机自启动
