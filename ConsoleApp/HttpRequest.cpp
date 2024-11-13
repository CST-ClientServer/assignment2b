#include "HttpRequest.hpp"
#include <iostream>
void HttpRequest::addFile(vector<char>& fileBytes, string name) {
    string fileSection;
    fileSection.append("--").append(boundary).append(separator);
    fileSection.append(contentDisposition).append(R"(form-data; name="File"; filename=")").append(name).append("\"").append(separator);
    fileSection.append("Content-Type: application/octet-stream").append(separator).append(separator);
    string fileAsStringBytes{fileBytes.begin(), fileBytes.end()};
    fileSection.append(fileAsStringBytes);
    requestComponents.push_back(fileSection);
}

void HttpRequest::addText(string text, string name) {
    string textSection;
    textSection.append("--").append(boundary).append(separator);
    textSection.append(contentDisposition).append("form-data; name=\"").append(name).append("\"").append(separator);
    textSection.append("Content-Type: text/plain").append(separator);
    textSection.append(separator).append(text).append(separator);
    requestComponents.push_back(textSection);
}

string HttpRequest::buildHeader(string host, string endpoint, int port) const {
    string header = "POST ";
    header.append(endpoint).append(" HTTP/1.1").append(separator);
    header.append("Host: ").append(host).append(":").append(to_string(port)).append(separator);
    header.append("Content-Type: ").append(contentType).append("; boundary=").append(boundary).append(separator);
    header.append("Connection: close");

    // calculate content size
    long totalBytes = header.size();
    for (string component : requestComponents) totalBytes += component.size();

    // set header to content size
    header.append("Content-Length: ").append(to_string(totalBytes)).append(separator);
    return header;
}

string HttpRequest::getRequestString(string host, string endpoint, int port) const {
    string httpRequest = buildHeader(host, endpoint, port);
    for(string component : requestComponents) httpRequest.append(component);
    return httpRequest;
}