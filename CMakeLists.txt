cmake_minimum_required(VERSION 3.13)
project(Server C)

set(CMAKE_C_STANDARD 99)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(./include)

aux_source_directory(./src/Server Server_SRCS)
aux_source_directory(./src/Client Client_SRCS)

add_executable(Server ${Server_SRCS})
add_executable(Client ${Client_SRCS})
