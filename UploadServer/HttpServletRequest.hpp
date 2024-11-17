#ifndef HTTPSERVLETREQUEST_HPP
#define HTTPSERVLETREQUEST_HPP

#include <sys/types.h>
#include <sys/unistd.h>
#include <sstream>
#include <iostream>
#include <string.h>

class HttpServletRequest {
public:
    // constructor
    explicit HttpServletRequest(int clientSocket) : clientSocket(clientSocket) {
        readRequest();
    }

    // reads data from the client socket into a provided buffer.
    // :param buffer: pointer to a char array where data is stored.
    // :param size: max number of bytes to read into the buffer.
    // returns the number of bytes read.
    ssize_t read(char* buffer, size_t size) {
        return ::read(clientSocket, buffer, size);
    }

    // destructor closes the client socket if it is open.
    ~HttpServletRequest() {
        if (clientSocket != -1) {
            ::close(clientSocket);
            clientSocket = -1;
        }
    }

    std::string getMethod() {
        return method;
    }

    std::string getPath() {
        return path;
    }

private:
    int clientSocket;  // socket file descriptor for the client connection
    std::string method;
    std::string path;

    void readRequest() {
        char buffer[1024];
        ssize_t totalBytesRead = 0;
        ssize_t bytesRead = 0;

        while ((bytesRead = ::read(clientSocket, buffer + totalBytesRead, sizeof(buffer) - totalBytesRead)) > 0) {
            totalBytesRead += bytesRead;
            std::cout << "Bytes read: " << bytesRead << std::endl;
            std::cout << "Total bytes read so far: " << totalBytesRead << std::endl;
            std::cout << "Bytes remaining in buffer: " << sizeof(buffer) - totalBytesRead << std::endl;

            if (strstr(buffer, "\r\n\r\n") != nullptr) {
                break;
            }
            if (totalBytesRead >= sizeof(buffer)) {
                std::cerr << "Buffer size exceeded" << std::endl;
                break;
            }
        }

        if (bytesRead <= 0) {
            std::cerr << "Error reading request." << std::endl;
            return;
        }

        buffer[totalBytesRead] = '\0';  // Null-terminate the string
        std::cout << "Request data: " << buffer << std::endl;

        std::string request(buffer);
        std::istringstream requestStream(request);

        requestStream >> method >> path;

        std::cout << "Method: " << method << std::endl;
        std::cout << "Path: " << path << std::endl;

        std::string line;

    }

};


#endif
