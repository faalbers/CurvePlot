cmake_minimum_required(VERSION 3.5)
project(CurvePlot VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH C:/Qt/6.1.1/mingw81_64)
#set(CMAKE_PREFIX_PATH /Users/frank/Qt/6.1.2/macos)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

file(GLOB CURVEPLOT_TARGETS *.cpp )
add_executable(CurvePlot ${CURVEPLOT_TARGETS})
target_link_libraries(CurvePlot PRIVATE Qt6::Widgets)
