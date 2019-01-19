cmake_minimum_required(VERSION 3.9)

project(Tests)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH /Users/miketerentyev/Qt/5.11.2/clang_64/lib/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_PREFIX_PATH /Users/miketerentyev/Qt/5.11.2/clang_64/)
find_package(Qt5Widgets REQUIRED)


find_package(Qt5Widgets REQUIRED)

add_library(MegaCleaner
        dataparser.cpp
        mainwindow.cpp
        mytreewidget.cpp
        progressdialog.cpp
        dataparser.h
        mainwindow.h
        mytreewidget.h
        action.h
        progressdialog.h
        mainwindow.ui
        progressdialog.ui
        )
add_executable(cleaner_testing
        tests/testing.cpp
        tests/gtest/gtest-all.cc
        tests/gtest/gtest.h
        tests/gtest/gtest_main.cc
        )
add_executable(cleaner
    main.cpp
    )

target_link_libraries(cleaner_testing MegaCleaner)
target_link_libraries(cleaner MegaCleaner)

qt5_use_modules(MegaCleaner Widgets)