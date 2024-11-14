#include "UploadServlet.hpp"

#include <fstream>
#include <iostream>

void UploadServlet::doPost(HttpServletRequest& req, HttpServletResponse& res) {
    // reading the file content from the request
    char buffer[1024];
    ssize_t bytesRead = 0;
    std::ostringstream fileContent;

    // read the content of the uploaded file
    while ((bytesRead = req.read(buffer, sizeof(buffer))) > 0) {
        fileContent.write(buffer, bytesRead);
    }

    // generate a unique file name
    std::string fileName = generateFileName();

    // save the uploaded file to disk
    saveFile(fileName, fileContent.str());

    // send a response with file details
    sendFileDetails(fileName, res);
}

std::string UploadServlet::generateFileName() {
    // get the current time in milliseconds since the epoch
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    // return a file name based on the current timestamp, e.g., "1636557200000.png"
    return std::to_string(milliseconds) + ".png";
}

void UploadServlet::saveFile(const std::string& fileName, const std::string& content) {
    // open the file in binary mode and write the content to it
    if (std::ofstream outFile(fileName, std::ios::binary); outFile.is_open()) {
        outFile.write(content.c_str(), content.size());
        outFile.close();
    } else {
        std::cerr << "Failed to save file: " << fileName << std::endl;
    }
}

void UploadServlet::sendFileDetails(const std::string& fileName, HttpServletResponse& res) {
    // get the current date and format it into a human-readable string
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string dateString = std::ctime(&now);
    dateString.erase(dateString.length() - 1); // erase /n

    // response message
    std::ostringstream responseMessage;
    responseMessage << "File uploaded successfully.\n";
    responseMessage << "File name: " << fileName << "\n";
    responseMessage << "Uploaded on: " << dateString << "\n";  // send current date

    // response message to the client
    res.write(responseMessage.str());
}