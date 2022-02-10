cmake_minimum_required(VERSION 3.2)
project(Timer)
add_executable(Timer main.cpp)
set_property(TARGET Timer PROPERTY CXX_STANDARD 17)
find_package(fmt)
target_link_libraries(Timer PUBLIC fmt::fmt)

