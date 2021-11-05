set(SOURCES src/FileMapper.c src/Search.c)

add_library(consistent STATIC ${SOURCES})

target_include_directories(consistent
        PUBLIC include/
        )

target_link_libraries(consistent PUBLIC coding)
target_link_libraries(consistent PUBLIC count_symbols_interface)
