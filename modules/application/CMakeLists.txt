set(SOURCES
    src/play/Game.cpp)

add_library(chess_application STATIC ${SOURCES})

target_include_directories(chess_application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(chess_application PRIVATE chess_core)
target_link_libraries(chess_application PRIVATE chess_filesystem)