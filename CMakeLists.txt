#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
file(GLOB_RECURSE source_files base/*.cpp hw/*.cpp ui/*.cpp)
add_executable (gameAmbiance main.cpp ${source_files})
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835 opencv_videoio)
#####################################
