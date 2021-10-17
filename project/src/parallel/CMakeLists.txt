set(SOURCES FileMapper.c ProcessFunctions.c)

add_library(parallel STATIC ${SOURCES})

target_include_directories(parallel
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )