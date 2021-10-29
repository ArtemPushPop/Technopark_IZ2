cmake_minimum_required(VERSION 3.15)
project(IZ2)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -ggdb3 -fsanitize=address -fsanitize=undefined")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -Wpedantic -ggdb3 -O3 -fsanitize=address -fsanitize=undefined")


set(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/project)
#configure main.h (data file setting)
set(DATA_FILE "${CMAKE_CURRENT_SOURCE_DIR}/data/data.txt")
configure_file("${PROJECT_FOLDER}/include/main.h.in" "${PROJECT_FOLDER}/include/main.h")
include_directories(${PROJECT_FOLDER}/include/)

# build libraries
add_subdirectory("${PROJECT_FOLDER}/src/")

option(PARALLEL "link parallel library" OFF)
option(CONSISTENT "link consistent library" OFF)
option(STRESS_TEST "Do stress test of libraries" OFF)
option(TESTS "Configure unit tests" OFF)


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
if (STRESS_TEST OR TESTS)
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


##tests
#option(ENABLE_COVERAGE "Build tests coverage statistic" OFF)
#if (ENABLE_COVERAGE)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -ftest-coverage -fprofile-arcs")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
#endif ()
#
#option(TEST "Build tests" OFF)
#if (TEST)
#    include(CTest)
#    include(FetchContent)
#    FetchContent_Declare(
#            googletest
#            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#    )
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#    FetchContent_MakeAvailable(googletest)
#
#    enable_testing()
#    include(CTest)
#
#    # Create binaries of tests
#
#    add_executable(test_car_low_level tests/test_car_low_level.cpp)
#    target_link_libraries(test_car_low_level gtest_main)
#    target_link_libraries(test_car_low_level car)
#    add_test(NAME AllTestsInCarLowLevel COMMAND test_car_low_level)
#
#
#    add_executable(test_cars_lib tests/test_cars_lib.cpp)
#    target_link_libraries(test_cars_lib gtest_main)
#    target_link_libraries(test_cars_lib car)
#    add_test(NAME AllTestsInCarsLib COMMAND test_cars_lib)
#
#    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts_cmake)
#    include(CodeCoverage)
#    # setup_target_for_coverage_gcovr_html(
#    #       NAME IZ1_coverage
#    #       EXECUTABLE ctest
#    #       BASE_DIRECTORY "${PROJECT_FOLDER}/src")
#    setup_target_for_coverage_gcovr_xml(
#            NAME IZ1_coverage
#            EXECUTABLE ctest
#            BASE_DIRECTORY "${PROJECT_FOLDER}/src")
#
#endif ()