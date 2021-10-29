add_executable(stress_test stress_test.c)

set(DATA_FILES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data_for_stress_test/")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/data_path.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/data_path.h")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(consistent_test "${PROJECT_FOLDER}/main.c")
add_executable(parallel_test "${PROJECT_FOLDER}/main.c")
target_link_libraries(consistent_test consistent)
target_link_libraries(parallel_test parallel)