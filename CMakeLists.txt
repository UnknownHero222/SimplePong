cmake_minimum_required(VERSION 3.16)
project(SimplePong)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(SimplePong main.cpp bat.cpp bat.h ball.cpp ball.h engine.cpp engine.h)

target_link_libraries(SimplePong sfml-graphics sfml-audio)