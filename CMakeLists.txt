cmake_minimum_required(VERSION 2.8)

project(tf)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(OpenCV REQUIRED)
add_executable(tf main.cpp projective_tf.cpp)
target_link_libraries(tf ${OpenCV_LIBS})
