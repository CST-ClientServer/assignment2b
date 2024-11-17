#include "UploadServerThread.hpp"

#include <iostream>
#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"
#include "UploadServlet.hpp"

UploadServerThread::UploadServerThread(int clientSocket) : clientSocket(clientSocket) {}

void* UploadServerThread::run(void* arg) {
    int clientSocket = *static_cast<int *>(arg);  // cast arg back to client socket

    try {
        // create request and response objects
        HttpServletRequest req(clientSocket);
        HttpServletResponse res(clientSocket);

        // instantiate UploadServlet for POST request
        UploadServlet uploadServlet;

        std::string path = req.getPath();
        std::string method = req.getMethod();

        std::cout<<path<<std::endl;
        std::cout<<method<<std::endl;

        if (path == "/" && method == "GET") {
            uploadServlet.doGet(req, res);  // Handle GET request for uploading form
        } else if (path == "/" && method == "POST") {
            uploadServlet.doPost(req, res); // Handle POST request for file upload
        } else {
            // Handle other paths, if necessary
            res.write("404 Not Found");
        }

        close(clientSocket);
    } catch (const std::exception& e) {
        std::cerr << "Error in UploadServerThread: " << e.what() << std::endl;
        close(clientSocket);
    }

    return nullptr;  // POSIX convention
}