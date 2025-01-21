cmake_minimum_required(VERSION 3.29)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer src/main.cpp
        src/Sphere.cpp
        src/HittableList.cpp
        src/Camera.cpp
        src/Interval.cpp
        src/Bbox.cpp
        src/Bvh.cpp
)

target_include_directories(RayTracer PUBLIC include/)