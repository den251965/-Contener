cmake_minimum_required(VERSION 3.0)

project(CreatFileofSetting )

set(SOURCES main.cpp)
add_executable(CreatFileofSetting ${SOURCES})

target_compile_features(CreatFileofSetting  PRIVATE cxx_std_17)