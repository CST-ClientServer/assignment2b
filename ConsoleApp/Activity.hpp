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
    void extractFileBytes(vector<byte>& byteVector);
public:
    Activity(string& fileName, int port) : imageFileName(fileName), uploader(port){};
    void runActivity();
};

#endif //ASSIGNMENT2B_ACTIVITY_HPP
