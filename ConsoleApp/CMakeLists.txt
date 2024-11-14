cmake_minimum_required(VERSION 3.27)
project(Assignment2b)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2b Driver.cpp
        UploadClient.cpp
        UploadClient.hpp
        HttpResponse.cpp
        HttpResponse.hpp
        HttpRequest.cpp
        HttpRequest.hpp
        Activity.cpp
        Activity.hpp)
