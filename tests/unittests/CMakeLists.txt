if (ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif ()


include(CTest)
if (GTEST_LOCAL)
    find_package(GTest REQUIRED)
    set(GTEST_LINK_LIBS GTest::gtest_main GTest::gtest)
else ()
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LINK_LIBS gtest_main gtest)
endif ()

enable_testing()


# Create binaries of tests

add_executable(unit_consistent_test test_consistent.cpp)
target_link_libraries(unit_consistent_test ${GTEST_LINK_LIBS})
target_link_libraries(unit_consistent_test consistent)
add_test(NAME AllTestsConsistent COMMAND unit_consistent_test)


add_executable(unit_parallel_test test_parallel.cpp)
target_link_libraries(unit_parallel_test ${GTEST_LINK_LIBS})
target_link_libraries(unit_parallel_test parallel)
add_test(NAME AllTestsParallel COMMAND unit_parallel_test)

add_executable(unit_coding test_coding.cpp)
target_link_libraries(unit_coding ${GTEST_LINK_LIBS})
target_link_libraries(unit_coding coding)
add_test(NAME AllTestsCoding COMMAND unit_coding)

# конфигурируем пути до тестовых файлов данных
configure_file("include/data_path.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/data_path.h")
target_include_directories(unit_consistent_test PUBLIC include)
target_include_directories(unit_parallel_test PUBLIC include)


# код кавереж
include(CodeCoverage)
setup_target_for_coverage_gcovr_xml(
        NAME IZ2_coverage
        EXECUTABLE ctest
        BASE_DIRECTORY "${PROJECT_FOLDER}/src")
