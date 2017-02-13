cmake_minimum_required(VERSION 2.8)
project(image-cpp-sdk)

set(CMAKE_C_COMPILER g++)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

file(GLOB_RECURSE cossdk_source_files "*.cpp")

add_library(imagesdk STATIC ${cossdk_source_files})
set_target_properties(imagesdk PROPERTIES OUTPUT_NAME "imagesdk")
