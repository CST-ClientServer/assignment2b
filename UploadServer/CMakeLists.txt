cmake_minimum_required(VERSION 3.27)
project(Assignment2b)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2b HttpServlet.hpp
        UploadServlet.hpp
        UploadServlet.cpp
        HttpServletRequest.hpp
        HttpServletResponse.hpp
        UploadServerThread.cpp
        UploadServerThread.hpp
        ServerSocket.cpp
        ServerSocket.hpp
        UploadServer.cpp)
