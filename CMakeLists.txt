cmake_minimum_required(VERSION 3.10)
project(g4-ne697)
set(APP_NAME sim)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${APP_NAME} ${SOURCES})