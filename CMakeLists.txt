cmake_minimum_required(VERSION 3.20)
project(noita_entity_search)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/ar")

set(LIBNOITABIN_SHARED_LIBRARY 1)
set(LIBBINARYIO_SHARED_LIBRARY 1)

add_subdirectory(lib)

add_executable(noita_entity_search main.cpp)
target_link_libraries(noita_entity_search PRIVATE noitabin args)
