#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/utsname.h>
#include <pwd.h>

using namespace std;

int main() {
    struct sysinfo info;
    struct utsname unameData;
    char hostname[1024];
    struct passwd *pw;
    uid_t uid;

    bool firstTime = true;

    while (true) {
        if (sysinfo(&info) != 0) {
            cerr << "Failed to get system information." << endl;
            return 1;
        }

        if (uname(&unameData) != 0) {
            cerr << "Failed to get uname information." << endl;
            return 1;
        }

        if (gethostname(hostname, sizeof(hostname)) != 0) {
            cerr << "Failed to get hostname." << endl;
            return 1;
        }

        uid = geteuid();
        pw = getpwuid(uid);
        if (pw == NULL) {
            cerr << "Failed to get user information." << endl;
            return 1;
        }

        string htmlContent = "<!DOCTYPE html>\n"
                             "<html>\n"
                             "<head>\n"
                             "    <title>System Information</title>\n"
                             "    <meta http-equiv=\"refresh\" content=\"5\">\n"
                             "    <style>\n"
                             "        body { font-family: Arial, sans-serif; margin: 40px; background-color: #f4f4f9; }\n"
                             "        h1 { color: #333; }\n"
                             "        .info { background-color: #fff; border-radius: 10px; padding: 20px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); margin-bottom: 20px; }\n"
                             "        .info p { margin: 0 0 10px; font-size: 18px; }\n"
                             "        .category { margin-top: 20px; }\n"
                             "    </style>\n"
                             "</head>\n"
                             "<body>\n"
                             "    <h1>System Information</h1>\n"
                             "    <div class=\"info\">\n"
                             "        <h2>General Information</h2>\n"
                             "        <p><strong>Hostname:</strong> " + string(hostname) + "</p>\n"
                             "        <p><strong>Operating System:</strong> " + string(unameData.sysname) + "</p>\n"
                             "        <p><strong>Node Name:</strong> " + string(unameData.nodename) + "</p>\n"
                             "        <p><strong>Release:</strong> " + string(unameData.release) + "</p>\n"
                             "        <p><strong>Version:</strong> " + string(unameData.version) + "</p>\n"
                             "        <p><strong>Machine:</strong> " + string(unameData.machine) + "</p>\n"
                             "        <p><strong>User Name:</strong> " + string(pw->pw_name) + "</p>\n"
                             "    </div>\n"
                             "    <div class=\"info\">\n"
                             "        <h2>Memory Information</h2>\n"
                             "        <p><strong>Total RAM:</strong> " + to_string(info.totalram / (1024 * 1024)) + " MB</p>\n"
                             "        <p><strong>Free RAM:</strong> " + to_string(info.freeram / (1024 * 1024)) + " MB</p>\n"
                             "        <p><strong>Shared RAM:</strong> " + to_string(info.sharedram / (1024 * 1024)) + " MB</p>\n"
                             "        <p><strong>Buffered RAM:</strong> " + to_string(info.bufferram / (1024 * 1024)) + " MB</p>\n"
                             "        <p><strong>Total Swap:</strong> " + to_string(info.totalswap / (1024 * 1024)) + " MB</p>\n"
                             "        <p><strong>Free Swap:</strong> " + to_string(info.freeswap / (1024 * 1024)) + " MB</p>\n"
                             "    </div>\n"
                             "</body>\n"
                             "</html>";

        ofstream outFile("system_info.html");
        if (outFile.is_open()) {
            outFile << htmlContent;
            outFile.close();
            cout << "HTML file has been created/updated successfully." << endl;
        } else {
            cerr << "Unable to open file for writing." << endl;
            return 1;
        }

        if (firstTime) {
            #ifdef _WIN32
                system("start system_info.html");
            #elif __APPLE__
                system("open system_info.html");
            #else
                system("xdg-open system_info.html");
            #endif
            firstTime = false;
        }

        usleep(5000 * 1000); // Sleep for 5000 milliseconds (5 seconds)
    }

    return 0;
}
