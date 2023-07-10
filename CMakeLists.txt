cmake_minimum_required(VERSION 3.25)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/amir/Qt/6.5.1/gcc_64/lib/cmake")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(game main.cpp Player.cpp Player.h Bullet.cpp Bullet.h MapCreator.cpp MapCreator.h Object.cpp Object.h Wall.cpp Wall.h Box.cpp Box.h Forest.cpp Forest.h Empty.cpp Empty.h
        resources.qrc Scene.cpp Scene.h)
target_link_libraries(game
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

