cmake_minimum_required(VERSION 3.20)
project(OOD2)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_library(${PROJECT_NAME} src/FileHandler.hpp src/FileHandler.cpp)

add_executable(${PROJECT_NAME}_first program1/main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_first PRIVATE ${PROJECT_NAME})
add_executable(${PROJECT_NAME}_second program2/main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_second PRIVATE ${PROJECT_NAME})
