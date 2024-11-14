#ifndef HTTPSERVLETRESPONSE_HPP
#define HTTPSERVLETRESPONSE_HPP

#include <unistd.h>
#include <cstddef>
#include <sys/socket.h>

class HttpServletResponse {
public:
    // constructor
    explicit HttpServletResponse(int clientSocket) : clientSocket(clientSocket) {}

    // returns the socket file descriptor used for writing data.
    int getOutputStream() {
        return clientSocket;
    }

    // writes data to the client socket.
    // param - buffer: pointer to the data to write to the socket.
    // param - size: number of bytes to write.
    // returns the number of bytes written.
    ssize_t write(const char* buffer, size_t size) {
        return ::write(clientSocket, buffer, size);
    }

    //  destructor closes the client socket if it is open.
    ~HttpServletResponse() {
        if (clientSocket != -1) {
            ::close(clientSocket);
            clientSocket = -1;
        }
    }

private:
    int clientSocket;  // socket file descriptor for the client connection.
};

#endif