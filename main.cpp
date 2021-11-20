#include <filesystem>
#include <string>
#include <iostream>
#include <functional>
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;

size_t fileCount = 0;
size_t fileSizeCount = 0;

void deleteFiles(fs::path path) {
    for (auto& p : fs::directory_iterator(path)) {
        if (p.is_directory()) {
            deleteFiles(p.path());
        }
        if (p.path().extension() == ".ipch") {
            fileCount++;
            fileSizeCount += fs::file_size(p.path());
            fs::remove(p.path());
            cout << "DELETED: " << p.path().string() << endl;
        }
    }
}

void cleanVSFolder(fs::path path) {
    for (auto& p : fs::directory_iterator(path)) {
        if (p.is_directory()) {
            if (p.path().filename() == ".vs") 
                deleteFiles(p.path());
            cleanVSFolder(p.path());
        }
    }
}

int main(int argc, char* argv[]) {
    string path;
    cout << "Visual Studio IPCH File cleaner | Author: Jasonzyt" << endl;
    cout << "=====================================================" << endl;
    if (argc == 1) path = fs::current_path().string();
    else if (argc == 2) path = argv[1];
    else {
        cout << "Usage: " << fs::path(argv[0]).filename() << " [path]" << endl;
        return 1;
    }
    cout << "Cleaning..." << endl;
    cleanVSFolder(path);
    cout << "=====================================================" << endl;
    cout << "Cleaned " << fileCount << " files, " 
    << fileSizeCount << " Bytes(" << fileSizeCount / 1024.0 / 1024.0 << " MB)" << endl;
    system("pause");
    return 0;
}