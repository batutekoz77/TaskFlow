#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <intrin.h>
#include <winioctl.h>
#include <iomanip>
#include <fstream>
#include <Windows.h>


void EnableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

std::unordered_map<std::string, std::string> parseMessage(const std::string& message) {
    std::unordered_map<std::string, std::string> data;
    std::istringstream stream(message);
    std::string line;
    while (std::getline(stream, line)) {
        size_t pos = line.find('|');
        if (pos != std::string::npos) {
            data[line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
    return data;
}

bool has(const std::unordered_map<std::string, std::string>& data, const std::string& key) {
    return data.find(key) != data.end() && !data.at(key).empty();
}

std::string get(const std::unordered_map<std::string, std::string>& data, const std::string& key) {
    auto it = data.find(key);
    return it != data.end() ? it->second : "";
}

bool isValidFullName(const std::string& name, size_t minLen = 3, size_t maxLen = 50) {
    if (name.size() < minLen || name.size() > maxLen) return false;
    std::string trimmed = name;
    trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    trimmed.erase(std::find_if(trimmed.rbegin(), trimmed.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), trimmed.end());
    std::istringstream iss(trimmed);
    std::vector<std::string> parts;
    std::string word;
    while (iss >> word) parts.push_back(word);
    if (parts.size() < 2) return false;

    return true;
}

bool isValidMail(const std::string& mail, size_t minBeforeAt = 3) {
    size_t atPos = mail.find('@');
    if (atPos == std::string::npos) return false;
    if (atPos < minBeforeAt) return false;
    size_t dotPos = mail.find('.', atPos);
    if (dotPos == std::string::npos) return false;
    if (dotPos == atPos + 1) return false;
    if (dotPos >= mail.size() - 2) return false;

    return true;
}

bool isValidPassword(const std::string& password) {
    if (password.size() < 6) return false;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    for (char ch : password) {
        if (std::isupper(static_cast<unsigned char>(ch))) hasUpper = true;
        else if (std::islower(static_cast<unsigned char>(ch))) hasLower = true;
        else if (std::isdigit(static_cast<unsigned char>(ch))) hasDigit = true;
        else hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

std::string getHWID() {
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Cryptography",
        0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
        return "";
    }

    char guid[256];
    DWORD size = sizeof(guid);
    if (RegQueryValueExA(hKey, "MachineGuid", NULL, NULL, (LPBYTE)guid, &size) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return "";
    }
    RegCloseKey(hKey);
    return std::string(guid);
}