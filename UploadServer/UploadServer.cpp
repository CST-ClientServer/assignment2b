#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "ServerSocket.hpp"
#include "UploadServerThread.hpp"
int main() {
    ServerSocket server(8082);  // Create server on port 8083
    pthread_t pthread;

    while (true) {
        std::cout<<"true"<<std::endl;
        int clientSocket = server.acceptConnection();  // accept client connection
        if (clientSocket < 0) {
            continue;  // continue to the next connection if accept fails
        }
        if (pthread_create(&pthread, nullptr, UploadServerThread::run, &clientSocket) != 0) {
            perror("create POSIX thread");
            close(clientSocket);  // close the socket if thread creation fails
            continue;
        } else {
            std::cout << "Thread created successfully!" << std::endl;
        }
        pthread_detach(pthread);  // detach the thread so it can clean up resources
    }

    server.closeSocket();  // Close the server socket
    return 0;
}