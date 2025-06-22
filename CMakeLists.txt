cmake_minimum_required(VERSION 3.5)

project(FK_Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


# Добавление исходных файлов
set(SOURCES
    src/gui/mainwindow.cpp
    src/gui/JointGroupBox.cpp
    src/gui/RobotGLWidget.cpp

    app/main.cpp
    src/RobotModel.cpp
    src/KinematicsCalculator.cpp
)

set(HEADERS
    include/gui/mainwindow.h
    include/gui/JointGroupBox.h
    include/gui/RobotGLWidget.h

    include/RobotModel.h
    include/KinematicsCalculator.h
)

# Создание исполняемого файла
add_executable(FK_Calculator ${SOURCES} ${HEADERS})

# Установка свойств целевого исполняемого файла
target_include_directories(FK_Calculator PRIVATE include)
target_link_libraries(FK_Calculator PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    OpenGL::GLU
    GLUT::GLUT
    Eigen3::Eigen
)

target_sources(FK_Calculator
  PRIVATE
)
