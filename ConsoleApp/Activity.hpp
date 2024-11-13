#ifndef ASSIGNMENT2B_ACTIVITY_HPP
#define ASSIGNMENT2B_ACTIVITY_HPP

#include <string>
#include <iostream>
#include <vector>
#include "UploadClient.hpp"

using namespace std;

class Activity {
    const string imageDirectory = "../Images/";
    string imageFileName;
    UploadClient uploader;

    // helper functions
    void extractFileBytes(vector<char>& byteVector) const;
    void printBodyContent(string content) const;
public:
    Activity(string& fileName, int port, const string& serverIp) : imageFileName(fileName), uploader(port, serverIp){};

    void runActivity();
};

#endif //ASSIGNMENT2B_ACTIVITY_HPP
