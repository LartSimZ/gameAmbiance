#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
file(GLOB_RECURSE source_files base/*.cpp base/*.h)
file(GLOB_RECURSE source_files hw/*.cpp hw/*.h)
file(GLOB_RECURSE source_files ui/*.cpp ui/*.h)
file(GLOB_RECURSE source_files main.cpp)
add_executable (gameAmbiance ${source_files})
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835)
#####################################
