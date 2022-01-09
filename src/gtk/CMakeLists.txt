if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message(FATAL_ERROR "Out of tree build mandatory. Use the Makefile (run make, not cmake)")
endif()

cmake_minimum_required(VERSION 3.5)

project(trh)

find_package(PkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

find_package(Threads REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -ldl -Og -g -ggdb")

include_directories("${PRJ_ROOT}") # In order to find the libs
include_directories("${PROJECT_SOURCE_DIR}/")
include_directories("${PROJECT_SOURCE_DIR}/src/gtk/")
include_directories(SYSTEM "${GTK3_INCLUDE_DIRS}")
include_directories(SYSTEM "${GTKMM_INCLUDE_DIRS}")

link_directories("${GTKMM_LIBRARY_DIRS}")

set(SRC main.cc DB.cc MainWindow.cc Vocabulary.cc Grammar.cc Log.cc ../lib/sqlite3.c)
set(HDR DB.hh db_tables.hh MainWindow.hh Vocabulary.hh Grammar.hh Log.hh ../lib/sqlite3.h)

add_executable(trh ${SRC} ${HDR})

target_link_libraries(trh dl Threads::Threads ${GTK3_LIBRARIES} ${GTKMM_LIBRARIES})
