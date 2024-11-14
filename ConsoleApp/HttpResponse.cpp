#include "HttpResponse.hpp"

#include <sstream>
#include <iostream>

HttpResponse::HttpResponse(string& response) : response(response) {
    stringstream stream{response};
    string buffer;
    int code;
    stream >> buffer >> code;
    statusCode = code;
}

string HttpResponse::extractBody() {
    // ignore header
    string bodyStartIdentifier = separator + separator;
    size_t bodyStart = response.find(bodyStartIdentifier);
    string startOfBody = response.substr(bodyStart);

    // determine chunk size
    int chunkSize = 0;
    stringstream stream{startOfBody};
    stream >> hex >> chunkSize;

    // get the body content
    string body = response.substr(bodyStart + stream.tellg(), chunkSize);
    return body;
}
