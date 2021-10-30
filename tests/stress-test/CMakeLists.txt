set(SOURCES stress_test.c src/ExeclArgsCreater.c src/TimeItExecl.c)
add_executable(stress_test ${SOURCES})

# конфигурируем пути до тестовых файлов данных
configure_file("include/data_path.h.in" "include/data_path.h")
target_include_directories(stress_test PUBLIC include)

add_executable(consistent_test "${PROJECT_FOLDER}/main.c")
add_executable(parallel_test "${PROJECT_FOLDER}/main.c")
target_link_libraries(consistent_test consistent)
target_link_libraries(parallel_test parallel)