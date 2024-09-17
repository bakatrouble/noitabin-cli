add_subdirectory(noitabin)

add_library(args INTERFACE)
target_include_directories(args INTERFACE ./args)
