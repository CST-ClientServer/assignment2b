#include "Activity.hpp"

#include <fstream>
#include <regex>

void Activity::runActivity() {
    // extract file bytes
    cout << "----Extracting File Bytes----" << endl;
    vector<byte> fileBytes;
    extractFileBytes(fileBytes);

    // get file name without extension
    size_t extensionPosition = imageFileName.find('.');
    string fileNameWithoutExtension = imageFileName.substr(0, extensionPosition);

    // call upload
    string responseContent = uploader.upload(fileBytes, imageFileName);
    cout << "----Response Content----" << endl;
    printBodyContent(responseContent);
}

void Activity::printBodyContent(string content) const {
    // print content directly if response was not html page
    if (content.find("<html>") < 0) {
        cout << content << endl;
        return;
    }
    // parse the html page for the listing
    regex const pattern{R"(<[^>]*>([^<]*\b\w+\.[^<]+)<\/[^>]*>)"};
    smatch matches;
    if (regex_match(content, matches, pattern)) {
        for (auto match : matches) {
            cout << match << endl;
        }
    }
}

void Activity::extractFileBytes(vector<byte>& byteVector) const {
    // open file
    ifstream file{imageDirectory + imageFileName, ios::binary};
    file.unsetf(ios::skipws);
    if (!file) {
        cout << "CRITICAL ERROR: file not found, exiting program" << endl;
        exit(1);
    }

    // adjust vector size
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    byteVector.reserve(fileSize);
    file.seekg(0, ios::beg);

    // read file and put into byteVector
    if(!file.read(reinterpret_cast<char*>(byteVector.data()), fileSize)) {
        cout << "An error occurred while trying to read the file, exiting program" << endl;
        exit(1);
    }
}