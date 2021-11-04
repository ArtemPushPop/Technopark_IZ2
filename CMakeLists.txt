cmake_minimum_required(VERSION 3.15)
project(IZ2)

# настройки проекта
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wpedantic)

# нужен абсолютный путь для формирования code coverage в tests/unittests/CMakeLists.txt
set(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

#configure main.h (data file setting)
set(DATA_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/data.txt)
configure_file(${PROJECT_FOLDER}/include/main.h.in ${PROJECT_FOLDER}/include/main.h)


option(PARALLEL "link parallel library")
option(CONSISTENT "link consistent library")
option(STRESS_TEST "Do stress test of libraries")
option(TESTS "Configure unit tests")
option(GTEST_LOCAL "Configured gtest on local machine?")
option(ENABLE_COVERAGE "Build tests coverage statistic")

# проверка в данный момент, так как библиотеки следует
# билдить с флагом кавереж
if (ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif ()


# build libraries
add_subdirectory("${PROJECT_FOLDER}/lib/")


if (STRESS_TEST OR TESTS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    enable_testing()
    add_subdirectory(tests)
    return()
endif ()


# make executable
add_executable(main ${PROJECT_FOLDER}/main.c)
target_include_directories(main PUBLIC ${PROJECT_FOLDER}/include/)
# link necessary libs
if (PARALLEL)
    target_link_libraries(main parallel)
elseif (CONSISTENT)
    target_link_libraries(main consistent)
else ()
    message(FATAL_ERROR "No library connected to project, default: Consistent.")
    target_link_libraries(main consistent)
endif ()
