cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(image_demo image_demo.cpp)
target_link_libraries(image_demo imagesdk curl ssl crypto rt jsoncpp stdc++ pthread z)
