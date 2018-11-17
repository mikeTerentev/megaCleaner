cmake_minimum_required(VERSION 3.10)

project("MegaCleaner")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

find_package(Qt5Widgets)


add_executable(filechecker main.cpp mainwindow.h
        mainwindow.cpp
        action.h
        dataparser.h
        dataparser.cpp
        )
target_link_libraries(filechecker stdc++fs Qt5::Widgets -lpthread -lstdc++fs)