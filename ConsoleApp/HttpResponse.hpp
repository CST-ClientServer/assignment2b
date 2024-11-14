#ifndef ASSIGNMENT2B_HTTPRESPONSE_HPP
#define ASSIGNMENT2B_HTTPRESPONSE_HPP

#include <string>
#include <utility>

using namespace std;

class HttpResponse {
    static constexpr string separator = "\r\n";
    string response;
    int statusCode;
public:
    explicit HttpResponse(string& response);
    string extractBody();
    [[nodiscard]] int getStatusCode() const { return statusCode; };
};

#endif //ASSIGNMENT2B_HTTPRESPONSE_HPP
