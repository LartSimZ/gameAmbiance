#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
add_executable (gameAmbiance main.cpp)  
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835)
#####################################
