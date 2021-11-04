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

# Create binaries of tests

add_executable(unit_consistent_test src/test_consistent.cpp)
target_link_libraries(unit_consistent_test ${GTEST_LINK_LIBS} consistent)
add_test(NAME AllTestsConsistent
        WORKING_DIRECTORY ${DATA_FILES_PATH}
        COMMAND unit_consistent_test)


add_executable(unit_parallel_test src/test_parallel.cpp)
target_link_libraries(unit_parallel_test ${GTEST_LINK_LIBS} parallel)
add_test(NAME AllTestsParallel
        WORKING_DIRECTORY ${DATA_FILES_PATH}
        COMMAND unit_parallel_test)

add_executable(unit_coding src/test_coding.cpp)
target_link_libraries(unit_coding ${GTEST_LINK_LIBS} coding)
add_test(NAME AllTestsCoding
        WORKING_DIRECTORY ${DATA_FILES_PATH}
        COMMAND unit_coding)

# код кавереж
if (ENABLE_COVERAGE)
    include(CodeCoverage)

    setup_target_for_coverage_gcovr_xml(
            NAME IZ2_coverage
            EXECUTABLE ctest
            BASE_DIRECTORY ${PROJECT_FOLDER}/lib)
endif ()
