#ifndef HTTPSERVLET_HPP
#define HTTPSERVLET_HPP

#include "HttpServletRequest.hpp"
#include "HttpServletResponse.hpp"

class HttpServlet {
public:
    virtual void doGet(HttpServletRequest& request, HttpServletResponse& response) = 0;
    virtual void doPost(HttpServletRequest& request, HttpServletResponse& response) = 0;
    virtual ~HttpServlet() = default;
};

#endif
