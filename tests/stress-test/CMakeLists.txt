set(SOURCES src/stress_test.c src/ExeclArgsCreater.c src/TimeItExecl.c)
add_executable(stress_test ${SOURCES})

# конфигурируем пути до тестовых файлов данных, необходимо использовать CMAKE_CURRENT_SOURCE_DIR
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/data_path.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/data_path.h")
target_include_directories(stress_test PUBLIC include)

add_executable(consistent_test "${PROJECT_FOLDER}/main.c")
add_executable(parallel_test "${PROJECT_FOLDER}/main.c")
target_include_directories(consistent_test PUBLIC ${PROJECT_FOLDER}/include/)
target_include_directories(parallel_test PUBLIC ${PROJECT_FOLDER}/include/)
target_link_libraries(consistent_test consistent)
target_link_libraries(parallel_test parallel)