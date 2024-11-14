#ifndef HTTPSERVLETRESPONSE_HPP
#define HTTPSERVLETRESPONSE_HPP

#include <string>
#include <unistd.h>

class HttpServletResponse {
public:
    explicit HttpServletResponse(int clientSocket) : clientSocket(clientSocket) {}

    // write data to the response
    void write(const std::string& data) {
        ::write(clientSocket, data.c_str(), data.size()); // write directly to the socket
    }

    ~HttpServletResponse() {
        // destructor to close socket
        if (clientSocket != -1) {
            ::close(clientSocket);
            clientSocket = -1;
        }
    }

private:
    int clientSocket; // Socket descriptor
};


#endif