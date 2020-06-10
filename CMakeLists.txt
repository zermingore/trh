if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message(FATAL_ERROR "Out of tree build advised.")
endif()


cmake_minimum_required(VERSION 3.5)

project(trh)

find_package(Threads REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -ldl")

include_directories("${PROJECT_SOURCE_DIR}/")

set(SRC src/main.cc lib/sqlite3.c)
set(HDR lib/sqlite3.h)
add_executable(trh ${SRC} ${HDR})

target_link_libraries(trh Threads::Threads)
