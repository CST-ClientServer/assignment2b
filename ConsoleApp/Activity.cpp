#include "Activity.hpp"
#include <fstream>

void Activity::runActivity() {
    // extract file bytes
    cout << "----Extracting File Bytes----" << endl;
    vector<byte> fileBytes;
    extractFileBytes(fileBytes);
    uploader.upload(fileBytes);
}

void Activity::extractFileBytes(vector<byte>& byteVector) {
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