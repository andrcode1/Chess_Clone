set(SOURCES
    src/placeholder.cpp
)

add_library(chess_gui STATIC ${SOURCES})

target_include_directories(chess_gui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(chess_gui PUBLIC chess_application)