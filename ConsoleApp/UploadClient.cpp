#include "UploadClient.hpp"

#include <utility>

sockaddr_in UploadClient::defineServer() const {
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
}

string UploadClient::upload(vector <byte> bytes) {
    cout << "----Creating client socket----" << endl;
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
    request.addText(caption);
    request.addText(date);
    request.addFile(std::move(bytes));

    cout << "----Sending Post Request----" << endl;
    // send post request
    string requestString = request.getRequestString();
    size_t sentBytes = send(clientSocket, requestString.c_str(), requestString.size(), 0);
    if (sentBytes < 0) {
        cout << "CRITICAL ERROR: failed to send data to server, exiting program" << endl;
        exit(1);
    }

    cout << "----Waiting For Server Response----" << endl;
    // get response data
    string responseString;
    size_t readBytes;
    char buffer[4096];
    readBytes = recv(clientSocket, buffer, sizeof(buffer), 0) > 0;
    while (readBytes) {
        responseString.append(buffer, readBytes);
        readBytes = recv(clientSocket, buffer, sizeof(buffer), 0) > 0;
    }

    cout << "----Closing Connection----" << endl;
    // close socket
    close(clientSocket);

    cout << "----Parsing Response----" << endl;
    HttpResponse response{responseString};
    if (response.getStatusCode() != 200) cout << "ERROR: returned status code of " << response.getStatusCode() << endl;
    return response.extractBody();
}
