cmake_minimum_required(VERSION 3.2...3.27.5)

project(kmms_prog_2023)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(npushkarev_bubble)
add_subdirectory(bubble_sort_mf)
add_subdirectory(refactoring)
add_subdirectory(smartSort)
add_subdirectory(obuchaika)
add_subdirectory(unit_test_example)
add_subdirectory(scl)

set(CMAKE_SUPPRESS_REGENERATION true)
