set(SOURCES src/FileMapper.c src/Search.c)

add_library(consistent STATIC ${SOURCES})

target_include_directories(consistent
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        )

target_link_libraries(consistent PUBLIC coding)