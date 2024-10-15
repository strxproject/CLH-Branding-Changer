#include <iostream>
#include <windows.h>
#include <filesystem>
#include <shlobj.h>
#include <cstdlib>

namespace fs = std::filesystem;

const std::string baseDir = "C:\\Classic Files\\Classic Setup\\CLH";
const std::string targetFile = "ConsoleLogonUI.dll";
const std::string system32Dir = "C:\\Windows\\System32";

void CopyBrandingDll(const std::string& branding) {
    std::string sourcePath = baseDir + "\\" + branding + "\\" + targetFile;
    std::string targetPath = system32Dir + "\\" + targetFile;

    if (fs::exists(sourcePath)) {
        if (fs::exists(targetPath)) {
            fs::remove(targetPath);
        }

        try {
            fs::copy_file(sourcePath, targetPath, fs::copy_options::overwrite_existing);
            std::cout << "Branding DLL successfully copied to " << targetPath << std::endl;
        }
        catch (fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "Branding folder or DLL not found: " << sourcePath << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3 || std::string(argv[1]) != "-branding") {
        std::cerr << "Usage: branding.exe -branding <Edition>" << std::endl;
        return 1;
    }

    std::string branding = argv[2];

    std::string validBrandings[] = { "Ultimate", "Professional", "Premium", "Basic", "Starter" };
    bool isValid = false;
    for (const auto& valid : validBrandings) {
        if (branding == valid) {
            isValid = true;
            break;
        }
    }

    if (!isValid) {
        std::cerr << "Invalid branding specified. Choose from: Ultimate, Professional, Home Premium, Home Basic, Starter." << std::endl;
        return 1;
    }

    CopyBrandingDll(branding);

    return 0;
}
