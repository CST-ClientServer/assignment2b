#ifndef ASSIGNMENT2B_HTTPREQUEST_HPP
#define ASSIGNMENT2B_HTTPREQUEST_HPP

#include <utility>
#include <vector>
#include <string>

using namespace std;

class HttpRequest {
    const string separator = "\r\n";
    const string boundary = "-------MyCustomBounds69420";
    const string contentDisposition = "Content-Disposition: ";

    vector<string> requestComponents;
    string contentType;
    string buildHeader(string host, string endpoint, int port) const;
public:
    explicit HttpRequest(string contentType = "multipart/form-data") : contentType(std::move(contentType)){};
    void addFile(vector<byte> fileBytes, string name);
    void addText(string text, string name);
    string getRequestString(string host, string endpoint, int port) const;
};

#endif //ASSIGNMENT2B_HTTPREQUEST_HPP
