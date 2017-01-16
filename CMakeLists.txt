#####################################
cmake_minimum_required (VERSION 2.8) 
project (gameAmbiance)
find_package(raspicam REQUIRED)
file(GLOB source_files "base/*.cpp")
file(GLOB source_files "hw/*.cpp" )
file(GLOB source_files "ui/*.cpp")
file(source_files "main.cpp")
add_executable (gameAmbiance ${source_files})
target_link_libraries (gameAmbiance ${raspicam_LIBS} bcm2835)
#####################################
