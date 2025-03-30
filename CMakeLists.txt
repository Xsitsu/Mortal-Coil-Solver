cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

project(solver VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(src)
