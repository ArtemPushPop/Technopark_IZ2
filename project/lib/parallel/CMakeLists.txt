set(SOURCES src/FileMapper.c src/ProcessFunctions.c)

add_library(parallel SHARED ${SOURCES})

target_include_directories(parallel
        PUBLIC include/
        )

target_link_libraries(parallel PUBLIC coding)
target_link_libraries(parallel PUBLIC count_symbols_interface)
