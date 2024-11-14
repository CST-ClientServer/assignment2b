#ifndef ASSIGNMENT2B_HTTPREQUEST_HPP
#define ASSIGNMENT2B_HTTPREQUEST_HPP

#include <utility>
#include <vector>
#include <string>

using namespace std;

class HttpRequest {
    const string separator = "\r\n";
    const string boundary = "d3f5Fjs8d7l2d9lEwJ6U3Shh4c9cG2Vw";
    const string contentDisposition = "Content-Disposition: ";

    vector<string> requestComponents;
    string contentType;
    string buildHeader(const string& host, const string& endpoint, int port) const;
public:
    explicit HttpRequest(string contentType = "multipart/form-data") : contentType(std::move(contentType)){};
    void addFile(vector<char>& fileBytes, const string& name);
    void addText(const string& text, const string& name);
    string getRequestString(const string& host, const string& endpoint, int port) const;
};

#endif //ASSIGNMENT2B_HTTPREQUEST_HPP
