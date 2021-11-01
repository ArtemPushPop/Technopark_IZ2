cmake_minimum_required(VERSION 3.15)
project(IZ2)

# для борьбы с оптимизированным выводом переменных в дебаге
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")


# настройки проекта
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -ggdb3 -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -Wpedantic -ggdb3 -O3 -fsanitize=address -fsanitize=undefined")


set(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/project)
#configure main.h (data file setting)
set(DATA_FILE "${CMAKE_CURRENT_SOURCE_DIR}/data/data.txt")
configure_file("${PROJECT_FOLDER}/include/main.h.in" "${PROJECT_FOLDER}/include/main.h")
include_directories(${PROJECT_FOLDER}/include/)

# build libraries
add_subdirectory("${PROJECT_FOLDER}/lib/")


option(PARALLEL "link parallel library" OFF)
option(CONSISTENT "link consistent library" OFF)
option(STRESS_TEST "Do stress test of libraries" OFF)
option(TESTS "Configure unit tests" OFF)
option(GTEST_LOCAL "gonfigured gtest on local machine?" ON)
option(ENABLE_COVERAGE "Build tests coverage statistic" OFF)


if (STRESS_TEST OR TESTS)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    enable_testing()
    add_subdirectory("tests")
    return()
endif ()


# make executable
add_executable(main "${PROJECT_FOLDER}/main.c")
# link necessary libs
if (PARALLEL)
    target_link_libraries(main parallel)
elseif (CONSISTENT)
    target_link_libraries(main consistent)
else ()
    message(FATAL_ERROR "No library connected to project, select one.")
endif ()
