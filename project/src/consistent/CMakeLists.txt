set(SOURCES FileMapper.c Search.c)

add_library(consistent STATIC ${SOURCES})

target_include_directories(consistent
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )