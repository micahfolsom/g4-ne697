cmake_minimum_required(VERSION 3.10)
project(g4-ne697)
set(APP_NAME sim)

# C++ options
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_FLAGS "-g -O2 -Wall -Wextra -Wpedantic")

# Geant4 setup
option(G4_VIS "Build with Geant4 visualization enabled" ON) 
if (G4_VIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME} ${Geant4_LIBRARIES})

add_custom_command(TARGET ${APP_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:${APP_NAME}>/scripts
)