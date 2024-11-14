#ifndef UPLOADSERVERTHREAD_HPP
#define UPLOADSERVERTHREAD_HPP

class UploadServerThread {
public:
    // constructor
    explicit UploadServerThread(int clientSocket);

    // thread entry point
    static void* run(void* arg);

private:
    int clientSocket;  // socket to communicate with the client
};

#endif
