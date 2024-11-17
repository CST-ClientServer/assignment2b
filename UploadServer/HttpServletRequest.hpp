#ifndef HTTPSERVLETREQUEST_HPP
#define HTTPSERVLETREQUEST_HPP

#include <sys/types.h>
#include <sys/unistd.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>

class HttpServletRequest {
public:
    // constructor
    explicit HttpServletRequest(int clientSocket) : clientSocket(clientSocket) {
        readRequestHeader();
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

    std::string getBoundary() {
        return boundary;
    }

    std::map<std::string, std::string> getFormData() {
        return formData;
    }

    std::vector<std::pair<std::string, std::string>> getFiles() {
        return files;
    }

    std::string getContent(){
        return content;
    }

private:
    int clientSocket;  // socket file descriptor for the client connection
    std::string method;
    std::string path;
    std::string boundary;
    std::string content;
    std::map<std::string, std::string> formData;  // stores form field data
    std::vector<std::pair<std::string, std::string>> files;

    void readRequestHeader () {
        char buffer[2048];
        ssize_t totalBytesRead = 0;
        ssize_t bytesRead = 0;
        std::ostringstream fileContent;
        while ((bytesRead = read(buffer, sizeof(buffer))) > 0) {
            totalBytesRead += bytesRead;
            fileContent.write(buffer, bytesRead);
            std::cout << "Bytes read: " << bytesRead << std::endl;
            std::cout << "Total bytes read so far: " << totalBytesRead << std::endl;
            if (bytesRead < sizeof buffer) {
                break;
            }
            if (totalBytesRead >= sizeof(buffer)) {
                std::cerr << "Buffer size exceeded" << std::endl;
                break;
            }
        }
        content = fileContent.str();

        buffer[totalBytesRead] = '\0';  // Null-terminate the string
        std::cout << "buffer: " << buffer << std::endl;

        //print out buffer content
        for (size_t i = 0; i < totalBytesRead; ++i) {
            if (buffer[i] == '\r') {
                std::cout << "\\r";
            } else if (buffer[i] == '\n') {
                std::cout << "\\n";
            } else if (isprint(buffer[i])) {
                std::cout << buffer[i];
            } else {
                std::cout << "\\x" << std::hex << (unsigned int)(unsigned char)buffer[i];
            }
        }
        std::cout << std::endl;

        std::string header(buffer);
        std::cout << "header: " << header << std::endl;
        std::istringstream requestStream(header);

        requestStream >> method >> path;

        std::cout << "Method: " << method << std::endl;
        std::cout << "Path: " << path << std::endl;

        if (method == "POST") {
            std::string line;
            while (std::getline(requestStream, line)) {
                if (line.find("Content-Type: multipart/form-data") != std::string::npos) {
                    size_t boundaryPos = line.find("boundary=");
                    if (boundaryPos != std::string::npos) {
                        // Extract the boundary and clean up the string
                        boundary = line.substr(boundaryPos + 9);
                        // Trim any leading or trailing whitespace
                        boundary.erase(0, boundary.find_first_not_of(" \t\r\n"));
                        boundary.erase(boundary.find_last_not_of(" \t\r\n") + 1);

                        if (boundary.back() == '/') {
                            boundary.pop_back();
                        }
                    }

                }
            }
        }

        //print out boundary
        std::cout << "boundary: " << std::endl;
        for (size_t i = 0; i < size(boundary); ++i) {
            if (boundary[i] == '\r') {
                std::cout << "\\r";
            } else if (boundary[i] == '\n') {
                std::cout << "\\n";
            } else if (isprint(boundary[i])) {
                std::cout << boundary[i];
            } else {
                std::cout << "\\x" << std::hex << (unsigned int)(unsigned char)boundary[i];
            }
        }


    }

};


#endif
