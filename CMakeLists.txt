cmake_minimum_required(VERSION 3.16)
project(FK_Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    app/*.cpp
)

file(GLOB_RECURSE HEADERS
    include/*.h
)

add_executable(FK_Calculator ${SOURCES} ${HEADERS})
target_include_directories(FK_Calculator PRIVATE include)

target_link_libraries(FK_Calculator PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    ${OPENGL_LIBRARIES}
    glut
    GLU
)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "fk-calculator")
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <your.email@example.com>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Forward Kinematics Calculator")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt6core6 (>= 6.2.0),
     libqt6gui6 (>= 6.2.0),
     libqt6widgets6 (>= 6.2.0),
     libqt6openglwidgets6 (>= 6.2.0),
     libglu1-mesa,
     libglut3.12,
     libxcb1,
     libeigen3-dev"
)

install(TARGETS FK_Calculator DESTINATION bin)

if(EXISTS ${CMAKE_SOURCE_DIR}/resources)
    install(DIRECTORY resources/ DESTINATION share/fk-calculator/resources)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/README.md)
    install(FILES README.md DESTINATION share/doc/fk-calculator)
endif()

include(CPack)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    find_package(OpenGL REQUIRED)

    target_link_libraries(FK_Calculator PRIVATE
        ${X11_X11_LIB}
        ${X11_Xext_LIB}
        ${OPENGL_gl_LIBRARY}
        GL
        GLU
    )
endif()
