cmake_minimum_required(VERSION 3.16)
project(doodle_jump)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML COMPONENTS graphics window system)

add_library(DoodleJumpLib Logic/Bonus.h Logic/Bonus.cpp
        Logic/Camera.h Logic/Camera.cpp
        Logic/Random.h Logic/Random.cpp
        Logic/Stopwatch.h Logic/Stopwatch.cpp
        Logic/World.h Logic/World.cpp
        Logic/EntityLogic.h Logic/EntityLogic.cpp
        Logic/Subject.h Logic/Subject.cpp
        Logic/AbstractFactory.h Logic/AbstractFactory.cpp
        Logic/Observer.h Logic/Observer.cpp
        Logic/IWindow.h Logic/IWindow.cpp)

add_executable(doodle_jump main.cpp
        Representation/Game.h Representation/Game.cpp
        Representation/Entity.h Representation/Entity.cpp
        Representation/ConcreteFactory.cpp Representation/ConcreteFactory.h
        Representation/Window.h Representation/Window.cpp
        )

target_link_libraries(doodle_jump DoodleJumpLib sfml-graphics sfml-window sfml-system)

add_custom_command(
        TARGET doodle_jump POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_BINARY_DIR}/src/)