#ifndef UPLOADSERVLET_HPP
#define UPLOADSERVLET_HPP

#include "HttpServlet.hpp"
#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"
#include <string>

class UploadServlet : public HttpServlet {
public:
    std::string filename;
    std::string caption;
    std::string date;
    std::string newFilename;

    void doGet(HttpServletRequest& request, HttpServletResponse& response) override;
    void doPost(HttpServletRequest& request, HttpServletResponse& response) override;

private:
    // get html form
    std::string getHtmlForm();

    // save the uploaded file content to disk
    void saveFile(const std::string& fileName, const std::string& content);

    // send the file upload success details to the response
    void sendFileDetails(const std::string& fileName, HttpServletResponse& res);
};

#endif
