cmake_minimum_required(VERSION 3.18.4)
project(raspberry_fan)
set(CMAKE_CXX_STANDARD 14)

add_executable(raspberry_fan main.cpp )
find_library(PIGPIOD_IF2_LIBRARY NAMES pigpiod_if2)
# 检查 pigpiod_if2 是否已找到
if(NOT PIGPIOD_IF2_LIBRARY)
    message(FATAL_ERROR "pigpiod_if2 library not found")
endif()
# 添加 pigpiod_if2 包含目录
include_directories(/usr/include)
target_link_libraries(raspberry_fan ${PIGPIOD_IF2_LIBRARY})