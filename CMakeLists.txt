cmake_minimum_required(VERSION 3.18.4)
project(raspberry_fan)
set(CMAKE_CXX_STANDARD 14)

add_executable(raspberry_fan main.cpp )
find_library(PIGPIO_LIBRARY NAMES pigpio)
# 检查 pigpio 是否已找到
if(NOT PIGPIO_LIBRARY)
    message(FATAL_ERROR "pigpio library not found")
endif()
# 添加 pigpio 包含目录
include_directories(/usr/include)
target_link_libraries(raspberry_fan ${PIGPIO_LIBRARY})