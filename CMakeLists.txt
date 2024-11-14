cmake_minimum_required(VERSION 3.27)
project(Assignment2b)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2b ConsoleApp/Driver.cpp
        ConsoleApp/UploadClient.cpp
        ConsoleApp/HttpResponse.cpp
        ConsoleApp/HttpRequest.hpp
        ConsoleApp/Activity.cpp
        UploadServer/HttpServlet.hpp
        UploadServer/main.cpp
        UploadServer/UploadServlet.cpp)
