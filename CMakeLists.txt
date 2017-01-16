#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
file(GLOB_RECURSE source_files base/*.cpp)
file(GLOB_RECURSE source_files hw/*.cpp )
file(GLOB_RECURSE source_files ui/*.cpp)
add_executable (gameAmbiance main.cpp ${source_files})
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835)
#####################################
