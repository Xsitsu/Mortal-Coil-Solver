set(target "solver")

add_executable(${target}
    BoardCommand.h
    BoardCommandDown.h
    BoardCommandDown.cpp
    BoardCommandLeft.h
    BoardCommandLeft.cpp
    BoardCommandRight.h
    BoardCommandRight.cpp
    BoardCommandSet.h
    BoardCommandSet.cpp
    BoardCommandUp.h
    BoardCommandUp.cpp
    
    Controller.h
    Controller.cpp

    Exceptions.h

    fileio.hpp
    fileio.cpp

    GameBoard.h
    GameBoard.cpp

    Guess.h
    Guess.cpp

    HttpService.h
    HttpService.cpp

    Logger.h
    Logger.cpp

    Switches.h

    main.cpp
)

target_include_directories("${target}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
