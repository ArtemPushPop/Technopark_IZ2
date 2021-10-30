# переменная для поиска путей до файлов данных для тестов
set(DATA_FILES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data_for_stress_test/")

if (STRESS_TEST)
    add_subdirectory(stress-test/)
endif ()

if (TESTS)
    add_subdirectory(unittests/)
endif ()
