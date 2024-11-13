#ifndef ASSIGNMENT2B_UPLOADCLIENT_HPP
#define ASSIGNMENT2B_UPLOADCLIENT_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

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

    // private helper functions

public:
    explicit UploadClient(int port) : route(portRoutes[port]){};
    void upload(vector<byte> bytes);
};

#endif //ASSIGNMENT2B_UPLOADCLIENT_HPP
