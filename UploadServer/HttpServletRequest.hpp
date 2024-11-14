#ifndef HTTPSERVLETREQUEST_HPP
#define HTTPSERVLETREQUEST_HPP

class HttpServletRequest {
public:
    // constructor
    explicit HttpServletRequest(int clientSocket) : clientSocket(clientSocket) {}

    // reads data from the client socket into a provided buffer.
    // :param buffer: pointer to a char array where data is stored.
    // :param size: max number of bytes to read into the buffer.
    // returns the number of bytes read.
    ssize_t read(char* buffer, size_t size) {
        return ::read(clientSocket, buffer, size);
    }

    ~HttpServletRequest() {
        if (clientSocket != -1) {
            ::close(clientSocket);
            clientSocket = -1;
        }
    }

private:
    int clientSocket;  // socket file descriptor for the client connection
};

#endif
