set(SOURCES
    src/placeholder.cpp
)

add_library(chess_filesystem STATIC ${SOURCES})

target_include_directories(chess_filesystem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)