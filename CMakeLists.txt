cmake_minimum_required(VERSION 3.18.4)
project(raspberry_pi)


set(CMAKE_CXX_STANDARD 14)

add_executable(raspberry_pi main.cpp)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(raspberry_pi ${WIRINGPI_LIBRARIES})