include_directories(../includes)


set(SOURCES music.cpp parser.cpp player.cpp playlist.cpp main.cpp display.cpp prompter_eval.cpp)
set(HEADERS ../includes/music.h ../includes/parser.h ../includes/player.h ../includes/playlist.h ../includes/display.h ../includes/prompter_eval.h)

add_executable(Onzer ${SOURCES} ${HEADERS})
