if (STRESS_TEST)
    add_subdirectory(stress-test/)
endif ()

if (TESTS)
    add_subdirectory(unittests/)
endif ()
