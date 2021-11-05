set(SOURCES src/CodingFeatures.c)

add_library(coding STATIC ${SOURCES})

target_include_directories(coding
        PUBLIC include
        )