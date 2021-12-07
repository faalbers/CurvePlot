cmake_minimum_required(VERSION 3.5)
project(CurvePlot VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

execute_process(COMMAND git submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_PREFIX_PATH C:/Qt/6.1.1/mingw81_64;C:/NumCpp)
set(CMAKE_PREFIX_PATH C:/Qt/6.1.1/mingw81_64)
#set(CMAKE_PREFIX_PATH /Users/frank/Qt/6.1.2/macos)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
#find_package(NumCpp)
#include_directories( C:/Eigen )

add_subdirectory(extern/ModelHierarchy)

file(GLOB CURVEPLOT_TARGETS *.cpp )
add_executable(CurvePlot ${CURVEPLOT_TARGETS})
#target_link_libraries(CurvePlot PRIVATE Qt6::Widgets NumCpp::NumCpp)
target_link_libraries(CurvePlot PRIVATE Qt6::Widgets ModelHierarchy)
target_include_directories(CurvePlot PRIVATE C:/eigen-3.4.0 ${CMAKE_CURRENT_SOURCE_DIR})
