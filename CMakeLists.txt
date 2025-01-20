cmake_minimum_required(VERSION 3.29)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        sphere.cpp
        sphere.h
        HittableList.cpp
        HittableList.h
        utility.h
        Interval.h
        Camera.cpp
        Camera.h
        Interval.cpp
        Material.h
)
