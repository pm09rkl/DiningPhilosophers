cmake_minimum_required(VERSION 3.0)

project(diningphilosophers)

add_executable(diningphilosophers main.cpp)

install(TARGETS diningphilosophers RUNTIME DESTINATION bin)
