#include "UploadServlet.hpp"

#include <fstream>
#include <iostream>

void UploadServlet::doGet(HttpServletRequest &request, HttpServletResponse &response) {
    std::ostringstream header;
    header << "HTTP/1.1 200 OK\r\n";
    header << "Content-Type: text/html; charset=UTF-8\r\n";
    header << "Content-Length: " << getHtmlForm().size() << "\r\n";
    header << "\r\n";

    response.write(header.str());
    std::string htmlForm = getHtmlForm();
    response.write(htmlForm);
}

void UploadServlet::doPost(HttpServletRequest& req, HttpServletResponse& res) {
    // reading the file content from the request
    char buffer[2048];
    ssize_t bytesRead = 0;
    std::ostringstream fileContent;

    // read the content of the uploaded file
    while ((bytesRead = req.read(buffer, sizeof(buffer))) > 0) {
        std::cout << "Bytes read!!!: " << bytesRead << std::endl;
        fileContent.write(buffer, bytesRead);
    }
    std::cout << "end " << bytesRead << std::endl;
    if (bytesRead <= 0) {
        std::cerr << "Error or no data read from request." << std::endl;
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

    // return a file name based on the current timestamp
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

std::string UploadServlet::getHtmlForm() {
    std::ostringstream oss;
    oss << "<!DOCTYPE html>"
        << "<html lang=\"en\">"
        << "<body>"
        << "<script src=\"https://cdn.tailwindcss.com\"></script>"
        << "<h2 class=\"text-2xl font-bold mb-6 text-center\">HTML Forms</h2>"
        << "<form action=\"http://localhost:8082/assignment_war/\" method=\"post\" enctype=\"multipart/form-data\""
           " class=\"max-w-lg mx-auto bg-gray-100 p-8 rounded-lg shadow-lg\">"
        << "<div class=\"mb-4\">"
        << "<label for=\"caption\" class=\"block text-lg font-semibold text-gray-700 mb-2\">Caption:</label>"
        << "<input type=\"text\" name=\"caption\" id=\"caption\" class=\"w-full px-3 py-2 border"
           " border-gray-300 rounded-lg shadow-sm focus:outline-none focus:border-blue-500 focus:ring-1"
           " focus:ring-blue-500\" placeholder=\"Enter caption\">"
        << "</div>"
        << "<div class=\"mb-4\">"
        << "<label for=\"date\" class=\"block text-lg font-semibold text-gray-700 mb-2\">Date:</label>"
        << "<input type=\"date\" name=\"date\" id=\"date\" class=\"w-full px-3 py-2 border border-gray-300"
           " rounded-lg shadow-sm focus:outline-none focus:border-blue-500 focus:ring-1 focus:ring-blue-500\">"
        << "</div>"
        << "<div class=\"mb-4\">"
        << "<label for=\"file\" class=\"block text-lg font-semibold text-gray-700 mb-2\">File:</label>"
        << "<input type=\"file\" name=\"File\" id=\"File\" accept=\"image/*,.txt\" class=\"w-full px-3 py-2 border"
           " border-gray-300 rounded-lg shadow-sm focus:outline-none focus:border-blue-500 focus:ring-1"
           " focus:ring-blue-500\">"
        << "</div>"
        << "<div class=\"text-center\">"
        << "<input type=\"submit\" value=\"Submit\" class=\"px-6 py-2 bg-blue-500 text-white font-semibold rounded-lg "
           "shadow-md hover:bg-blue-600 focus:outline-none focus:ring-2 focus:ring-blue-500 focus:ring-opacity-50\">"
        << "</div>"
        << "</form>"
        << "</body>"
        << "</html>";

    return oss.str();
}