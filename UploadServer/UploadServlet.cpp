#include "UploadServlet.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>

void ensureDirectoryExists(const std::string& dirPath) {
    if (!std::filesystem::exists(dirPath)) {
        try {
            std::filesystem::create_directories(dirPath);
            std::cout << "Directory created: " << dirPath << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error creating directory: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Directory already exists: " << dirPath << std::endl;
    }
}
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

    std::ostringstream fileResponse;
    fileResponse << "HTTP/1.1 200 OK\r\n";
    fileResponse << "Access-Control-Allow-Origin: *\r\n";
    fileResponse << "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n";
    fileResponse << "Access-Control-Allow-Headers: Content-Type, Authorization\r\n";
    fileResponse << "\r\n";

    res.write(fileResponse.str());

    // reading the file content from the request
    char buffer[2048];
    ssize_t bytesRead = 0;
    std::ostringstream fileContent;

//    // read the content of the uploaded file
//    while ((bytesRead = req.read(buffer, sizeof(buffer))) > 0) {
//        std::cout << "Bytes read!!!: " << bytesRead << std::endl;
//        fileContent.write(buffer, bytesRead);
//        if (bytesRead < sizeof buffer) {
//            break;
//        }
//    }
    std::cout << "end " << std::endl;

    // save the uploaded file to disk
//    saveFile(fileName, fileContent.str());
    std::string body = req.getContent();
    std::string boundary = req.getBoundary();
    size_t boundaryPos = 0;
    size_t startPos = 0;

    while ((boundaryPos = body.find(boundary, startPos)) != std::string::npos) {
        startPos = boundaryPos + boundary.size() + 2;
        size_t endPos = body.find(boundary, startPos);

        if (endPos == std::string::npos) {
            break;
        }

        std::string part = body.substr(startPos, endPos - startPos);

        auto cleanString = [](std::string& str) {
            str.erase(std::remove_if(str.begin(), str.end(), [](const char c) {
                return !std::isalnum(c);
            }), str.end());
            str += "--";
        };

        size_t contentDispositionPos = part.find("Content-Disposition: ");
    if (contentDispositionPos != std::string::npos) {
        size_t captionPos = part.find("name=\"caption\"", contentDispositionPos);
        if (captionPos != std::string::npos) {
            size_t valuePos = part.find("\r\n\r\n", contentDispositionPos);
            if (valuePos != std::string::npos) {
                caption = part.substr(valuePos + 4);
                cleanString(caption);
                std::cout << "Caption: " << caption << std::endl;
            }
        }
        size_t datePos = part.find("name=\"date\"", contentDispositionPos);
        if (datePos != std::string::npos) {
            size_t valuePos = part.find("\r\n\r\n", contentDispositionPos);
            if (valuePos != std::string::npos) {
                date = part.substr(valuePos + 4);
                cleanString(date);
                std::cout << "Date: " << date << std::endl;
            }
        }
        // Check for file fields like 'filename'
        size_t filenamePos = part.find("filename=\"", contentDispositionPos);
        if (filenamePos != std::string::npos) {
            filenamePos += 10;  // Skip 'filename="'
            size_t filenameEndPos = part.find("\"", filenamePos);
            std::string filename = part.substr(filenamePos, filenameEndPos - filenamePos);
            newFilename = date + caption + filename;
            size_t fileContentPos = part.find("\r\n\r\n", contentDispositionPos);
            if (fileContentPos != std::string::npos) {
                std::string fileContent = part.substr(fileContentPos + 4);
                std::string dirPath = "../images";
                ensureDirectoryExists(dirPath);
                saveFile("../images/" + newFilename, fileContent);
            }
        }
    }
    startPos = endPos;  // Move to the next part
}
    // send a response with file details
    sendFileDetails(newFilename, res);
}

void UploadServlet::saveFile(const std::string& fileName, const std::string& content) {
    std::ofstream outFile(fileName, std::ios::binary);  // Open file in binary mode
    if (outFile.is_open()) {
        outFile.write(content.c_str(), content.size());  // Write the file content
        outFile.close();  // Close the file after writing
        std::cout << "File saved as: " << fileName << std::endl;
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
        << "<form action=\"http://localhost:8082/\" method=\"post\" enctype=\"multipart/form-data\""
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