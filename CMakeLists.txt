cmake_minimum_required(VERSION 2.8)
set ( CMAKE_CXX_STANDARD 11 )
project( cpp_code )
find_package( OpenCV REQUIRED )
#find_package(OPENCV COMPONENTS core imgproc highgui REQUIRED)
#find_package(Qt COMPONENTS QtOpenGL QtXml REQUIRED)
#find_package(OpenCL REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
set( SOURCES *.cpp *.h )
add_executable( dirac dirac.cpp )
target_link_libraries( dirac ${OpenCV_LIBS} )
