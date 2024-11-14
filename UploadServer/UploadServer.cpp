#include <functional>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "UploadServerThread.hpp"

void main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr{};
    pthread_t pthread;

    if (serverSocket < 0) {
        perror("opening stream socket");
        std::cerr << std::endl;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // bind to any available network interface
    serverAddr.sin_port = htons(8082);  // set the port number

    // bind the socket to the address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("binding stream socket");
        std::cerr << std::endl;
    }

    //  listening for incoming connections
    if (listen(serverSocket, 5) < 0) {
        perror("listening stream socket");
        std::cerr << std::endl;
    }

    std::cout << "Server is listening on port " << serverAddr.sin_port << std::endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);  // accept client connection
        if (clientSocket < 0) {
            perror("accept client connection");
            std::cerr << std::endl;
            continue;  // continue to the next connection if accept fails
        }

        // POSIX thread and pass the client socket

        if (pthread_create(&pthread, nullptr, UploadServerThread::run, &clientSocket) != 0) {
            perror("create POSIX thread");
            std::cerr << std::endl;
            close(clientSocket);  // close the socket if thread creation fails
            continue;
        }

        // detach the thread so it can clean up resources when finished
        pthread_detach(pthread);
    }
}