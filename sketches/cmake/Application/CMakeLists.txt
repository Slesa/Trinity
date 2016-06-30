cmake_minimum_required(VERSION 2.8.12)
project(Application)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(BIN_INSTALL_DIR "bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${BIN_INSTALL_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${LIB_INSTALL_DIR})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5 COMPONENTS Quick Core)
#find_package(Qt5QuickCompiler)
qt5_add_resources(RESOURCES qml.qrc)
#qtquick_compiler_add_resources(RESOURCES qml.qrc)

include_directories(${Qt5Widgets_INCLUDES})

add_definitions(${Qt5Widgets_DEFINITIONS})

add_executable(Application main.cpp ${RESOURCES})
qt5_use_modules(Application Quick Core)

