#include "Activity.hpp"

#include <fstream>
#include <regex>

void Activity::runActivity() {
    // extract file bytes
    cout << "----Extracting File Bytes----" << endl;
    vector<char> fileBytes;
    extractFileBytes(fileBytes);

    // get file name without extension
    size_t extensionPosition = imageFileName.find('.');
    string fileNameWithoutExtension = imageFileName.substr(0, extensionPosition);

    // call upload
    string responseContent = uploader.upload(fileBytes, imageFileName);
    cout << "----Response Content----" << endl;
    printBodyContent(responseContent);
}

void Activity::printBodyContent(string& content) {
    // print content directly if response was not html page
    if (content.find("<html>") < 0) {
        cout << content << endl;
        return;
    }
    // parse the html page for the listing
    regex const pattern{R"(<[^>]*>([^<]*\b\w+\.[^<]+)<\/[^>]*>)"};
    smatch matches;
    auto startPoint = content.cbegin();
    while(regex_search(startPoint, content.cend(), matches, pattern)) {
        cout << matches[1] << endl;
        startPoint = matches[0].second;
    }
}

void Activity::extractFileBytes(vector<char>& byteVector) const {
    // open file
    ifstream file{imageDirectory + imageFileName, ios::binary};
    if (!file) {
        cout << "CRITICAL ERROR: file not found, exiting program" << endl;
        exit(1);
    }
    byteVector.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}