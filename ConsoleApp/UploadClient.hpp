#ifndef ASSIGNMENT2B_UPLOADCLIENT_HPP
#define ASSIGNMENT2B_UPLOADCLIENT_HPP

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

using namespace std;

class UploadClient {
    // hard coded details
    map<int, string> portRoutes = {
            {8081, "/upload/upload"},
            {8082, "/assignment_war/"}
    };
    static constexpr string caption = "pain";
    static constexpr string date = "2024-4-20";
    static constexpr string host = "localhost";

    // data members
    string route;
    string serverIp;
    int port;

    // private helper functions
    [[nodiscard]] sockaddr_in defineServer() const;
public:
    explicit UploadClient(int port, string serverIp) : route(portRoutes[port]), port(port), serverIp(std::move(serverIp)){};
    string upload(vector<char>& bytes, const string& fileName);
};

#endif //ASSIGNMENT2B_UPLOADCLIENT_HPP
