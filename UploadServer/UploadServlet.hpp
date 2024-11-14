#ifndef UPLOADSERVLET_HPP
#define UPLOADSERVLET_HPP

#include "HttpServlet.hpp"

class UploadServlet : public HttpServlet {
public:
    void doGet(int clientSocket) override;
    void doPost(int clientSocket) override;
};

#endif
