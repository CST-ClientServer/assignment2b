#ifndef UPLOADSERVLET_HPP
#define UPLOADSERVLET_HPP

#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"
#include <string>
#include <chrono>

class UploadServlet {
public:
    // handle the POST request for file upload
    void doPost(HttpServletRequest& req, HttpServletResponse& res);

private:
    // generate a unique file name based on current date
    std::string generateFileName();

    // save the uploaded file content to disk
    void saveFile(const std::string& fileName, const std::string& content);

    // send the file upload success details to the response
    void sendFileDetails(const std::string& fileName, HttpServletResponse& res);
};

#endif
