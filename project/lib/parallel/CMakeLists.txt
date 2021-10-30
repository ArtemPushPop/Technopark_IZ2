set(SOURCES src/FileMapper.c src/ProcessFunctions.c)

add_library(parallel SHARED ${SOURCES})

target_include_directories(parallel
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )