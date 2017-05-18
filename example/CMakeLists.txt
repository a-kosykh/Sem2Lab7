cmake_minimum_required(VERSION 2.8)

project (Sem2Lab7_example)
set(SOURCES Source.cpp)
add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Sem2Lab7)