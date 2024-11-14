#include "UploadClient.hpp"

sockaddr_in UploadClient::defineServer() const {
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(serverIp.c_str());
    return serverAddress;
}

string UploadClient::upload(vector<char>& bytes, const string& fileName) {
    cout << "----Creating Client socket----" << endl;
    // create client socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        cout << "CRITICAL ERROR: failed to create socket, exiting program" << endl;
        exit(1);
    }
    cout << "----Establishing Connection With Server----" << endl;
    // connect to server
    sockaddr_in destinationServer = defineServer();
    if (connect(clientSocket, (struct sockaddr*)&destinationServer, sizeof(destinationServer)) < 0) {
        cout << "CRITICAL ERROR: failed to connect to server, exiting program" << endl;
        exit(1);
    }
    cout << "----Preparing Post Request----" << endl;
    // build http request
    HttpRequest request{};
    request.addText(caption, "caption");
    request.addText(date, "date");
    request.addFile(bytes, fileName);

    cout << "----Sending Post Request----" << endl;
    // send post request
    string requestString = request.getRequestString(host, route, port);
    size_t sentBytes = send(clientSocket, requestString.c_str(), requestString.size(), 0);
    if (sentBytes <= 0) {
        cout << "CRITICAL ERROR: failed to send data to server, exiting program" << endl;
        exit(1);
    }

    cout << "----Waiting For Server Response----" << endl;
    // get response data
    string responseString;
    size_t bufferSize = 1024, bytesRead;
    char buffer[bufferSize];
    while((bytesRead = recv(clientSocket, buffer, bufferSize, 0)) >= 0) {
        responseString.append(buffer, bytesRead);
        if (bytesRead < bufferSize) break;
    }

    cout << "----Closing Connection----" << endl;
    // close socket
    close(clientSocket);

    cout << "----Parsing Response----" << endl;
    HttpResponse response{responseString};
    if (response.getStatusCode() != 200) cout << "WARNING: returned status code of " << response.getStatusCode() << endl;
    return response.extractBody();
}
