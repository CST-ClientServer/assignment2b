#include "Activity.hpp"
#include <string>

using namespace std;

// 8081 for the demo upload servlet
// 8082 for the assignment2 server (both Java/C++)
constexpr int PORT = 8081;

int main(int argc, const char* argv[]) {
    string serverIp = "127.0.0.1"; // localhost
    if (argc == 2) serverIp = argv[1];
    string fileName = "meme.jpg";
    Activity activity{fileName, PORT, serverIp};
    activity.runActivity();
}
