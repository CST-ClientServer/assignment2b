#include "HttpResponse.hpp"

#include <sstream>

HttpResponse::HttpResponse(string response) : response(std::move(response)) {
    stringstream stream{response};
    string buffer;
    stream >> buffer >> statusCode;
}

string HttpResponse::extractBody() {
    string bodyStartIdentifier = separator + separator;
    size_t bodyStart = response.find(bodyStartIdentifier);
    string body = response.substr(bodyStart + bodyStartIdentifier.size());
    return body;
}
