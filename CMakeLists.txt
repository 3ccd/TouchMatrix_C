cmake_minimum_required(VERSION 3.16)
project(TouchMatrix)

set(CMAKE_CXX_STANDARD 14)

add_executable(TouchMatrix main.cpp Selector.cpp Selector.h Singleton.h Led.cpp Led.h SpiAdc.cpp SpiAdc.h TouchMatrix.cpp TouchMatrix.h)

target_link_libraries(TouchMatrix wiringPi)