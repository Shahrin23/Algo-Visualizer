cmake_minimum_required(VERSION 3.16)

project(AlgoVisualizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AlgoVisualizer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        sortvisualizer.h sortvisualizer.cpp
        graphvisualizer.h graphvisualizer.cpp
        treevisualizer.h treevisualizer.cpp
    )
else()
    add_executable(AlgoVisualizer
        ${PROJECT_SOURCES}
        sortvisualizer.h sortvisualizer.cpp
        graphvisualizer.h graphvisualizer.cpp
        treevisualizer.h treevisualizer.cpp
    )
endif()

target_link_libraries(AlgoVisualizer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(AlgoVisualizer PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AlgoVisualizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AlgoVisualizer)
endif()
