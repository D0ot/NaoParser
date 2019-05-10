cmake_minimum_required(VERSION 3.0)

project(learnse)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

set(SHARED_SOURCES naometadata.cpp sexpresso.cpp)

set(MAIN_SOURCES main.cpp)

set(UNITTEST_SOURCES unittest.cpp)

add_executable(main ${MAIN_SOURCES} ${SHARED_SOURCES})

add_executable(unittest ${UNITTEST_SOURCES} ${SHARED_SOURCES})



