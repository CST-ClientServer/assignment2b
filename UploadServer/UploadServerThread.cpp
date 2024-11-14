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

        // servlet's doPost to process the file upload
        uploadServlet.doPost(req, res);

        close(clientSocket);
    } catch (const std::exception& e) {
        std::cerr << "Error in UploadServerThread: " << e.what() << std::endl;
        close(clientSocket);
    }

    return nullptr;  // POSIX convention
}