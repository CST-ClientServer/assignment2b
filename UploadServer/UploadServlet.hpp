#ifndef UPLOADSERVLET_HPP
#define UPLOADSERVLET_HPP

#include "HttpServlet.hpp"
#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"
#include <string>
#include <chrono>


class UploadServlet : public HttpServlet {
public:
    void doGet(HttpServletRequest& request, HttpServletResponse& response) override;
    void doPost(HttpServletRequest& request, HttpServletResponse& response) override;

private:
    // get html form
    std::string getHtmlForm();

    // generate a unique file name based on current date
    std::string generateFileName();

    // save the uploaded file content to disk
    void saveFile(const std::string& fileName, const std::string& content);

    // send the file upload success details to the response
    void sendFileDetails(const std::string& fileName, HttpServletResponse& res);
};

#endif
