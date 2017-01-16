#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
add_executable (gameAmbiance main.cpp)
file(GLOB_RECURSE sources hw/*.cpp hw/*.h)
file(GLOB_RECURSE sources ui/*.cpp ui/*.h)
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835)
#####################################
