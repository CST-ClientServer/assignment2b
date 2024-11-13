#include "Activity.hpp"

using namespace std;

// 8081 for the demo upload servlet
// 8082 for the assignment2 server (both Java/C++)
constexpr int PORT = 8081;

int main() {
    string fileName = "meme.jpg";
    Activity activity{fileName, PORT};
    activity.runActivity();
}
