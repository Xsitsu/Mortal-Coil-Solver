set(target "solver")

add_executable(${target}
    board_command/BoardCommand.h
    board_command/BoardCommandDown.h
    board_command/BoardCommandDown.cpp
    board_command/BoardCommandLeft.h
    board_command/BoardCommandLeft.cpp
    board_command/BoardCommandRight.h
    board_command/BoardCommandRight.cpp
    board_command/BoardCommandSet.h
    board_command/BoardCommandSet.cpp
    board_command/BoardCommandUp.h
    board_command/BoardCommandUp.cpp
    
    Controller.h
    Controller.cpp

    Exceptions.h

    GameBoard.h
    GameBoard.cpp

    Guess.h
    Guess.cpp

    Switches.h

    http/http_handler.hpp
    http/http_handler.cpp
    http/http_cache.hpp
    http/http_cache.cpp

    main.cpp
)

target_include_directories("${target}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries("${target}"
    PRIVATE
        libcurl.so
)
