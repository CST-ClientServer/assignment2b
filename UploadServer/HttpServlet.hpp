#ifndef HTTPSERVLET_HPP
#define HTTPSERVLET_HPP

class HttpServlet {
public:
    virtual void doGet(int clientSocket) = 0;
    virtual void doPost(int clientSocket) = 0;
    virtual ~HttpServlet() = default;
};

#endif
