cmake_minimum_required(VERSION 3.5)
project(tic_tac_toe_allegro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c game.c)

INCLUDE_DIRECTORIES(/usr/include/)
LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)

add_executable(tic_tac_toe_allegro ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(tic_tac_toe_allegro
        allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)
