cmake_minimum_required (VERSION 3.5)
project (SeastarExercise)

find_package (Seastar REQUIRED)
add_library(Valgrind::valgrind INTERFACE IMPORTED)

add_executable (helloworld helloworld.cc)
target_link_libraries (helloworld PRIVATE Seastar::seastar)
