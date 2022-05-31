CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(server)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${BINARY} main.cpp)

add_subdirectory(Server ThreadPool)

include_directories(Server ThreadPool)

target_link_libraries(${BINARY} PUBLIC
                      ${BINARY}_server ${BINARY}_thread_pool)
