#define _SILENCE_CXX20_CODECVT_FACETS_DEPRECATION_WARNING

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <random>
#include <memory>
#include <algorithm>

#include <curl/curl.h>
#include <SFML/Network.hpp>

#include "Database/UsersBase.hpp"


const std::string GMAIL_USERNAME = "";
const std::string GMAIL_APP_PASSWORD = "";

UsersBase usersDb("UsersBase.db");

struct ClientInfo {
    std::shared_ptr<sf::TcpSocket> socket;
    std::string fullname;
    std::string email;
    std::string password;
    std::string verificationCode;
    std::string hwid;
};

std::unordered_map<std::string, ClientInfo> activeClients;
std::mutex clientsMutex;
std::mutex coutMutex;

struct MemoryStruct {
    const char* payload_ptr;
    size_t bytes_left;
};

static size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) {
    auto& mem = *static_cast<MemoryStruct*>(userp);
    size_t copy_len;
    if (mem.bytes_left < size * nmemb) copy_len = mem.bytes_left;
    else copy_len = size * nmemb;
    if (copy_len > 0) {
        memcpy(ptr, mem.payload_ptr, copy_len);
        mem.payload_ptr += copy_len;
        mem.bytes_left -= copy_len;
        return copy_len;
    }
    return 0;
}

bool sendGmail(const std::string& to, const std::string& subject, const std::string& body) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    struct curl_slist* recipients = nullptr;
    recipients = curl_slist_append(recipients, to.c_str());

    std::string email_payload =
        "To: <" + to + ">\r\n"
        "From: <" + GMAIL_USERNAME + ">\r\n"
        "Subject: " + subject + "\r\n"
        "\r\n"
        + body;

    MemoryStruct mem = { email_payload.c_str(), email_payload.length() };

    curl_easy_setopt(curl, CURLOPT_USERNAME, GMAIL_USERNAME.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, GMAIL_APP_PASSWORD.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, GMAIL_USERNAME.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &mem);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

std::string generateVerificationCode() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
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

void sendPacket(std::shared_ptr<sf::TcpSocket> client, const std::string& msg) {
    if (!client) return;

    sf::Socket::Status status = client->send(msg.c_str(), msg.size());
    if (status != sf::Socket::Status::Done) {
        std::unique_lock<std::mutex> coutLock(coutMutex);
        std::cerr << "Failed to send message to client "
            << (client->getRemoteAddress().has_value() ? client->getRemoteAddress()->toString() : "unknown")
            << "\n";
    }
}

void handleClient(std::shared_ptr<sf::TcpSocket> client, const std::string& clientIP) {
    {
        std::unique_lock<std::mutex> lock(coutMutex);
        std::cout << "Client connected: " << clientIP << ":" << client->getRemotePort() << "\n";
    }

    while (true) {
        char buffer[1024];
        std::size_t received;
        sf::Socket::Status status = client->receive(buffer, sizeof(buffer), received);

        if (status == sf::Socket::Status::Done) {
            std::string msg(buffer, received);
            auto data = parseMessage(msg);

            if (data["action"] == "email_verification" && has(data, "fullname") && has(data, "mail") && has(data, "password")) {
                std::string code = generateVerificationCode();

                std::string body =
                    "Hi " + get(data, "fullname") + ",\n\n"
                    "Thank you for registering with TaskFlow!\n\n"
                    "Your verification code is: " + code + "\n\n"
                    "Your account information:\n"
                    "Full Name: " + get(data, "fullname") + "\n"
                    "Email: " + get(data, "mail") + "\n"
                    "Password: " + get(data, "password") + "\n\n"
                    "Best regards,\nTaskFlow Team";

                std::string recipient = get(data, "mail");
                std::string subject = "TaskFlow Email Verification";

                std::thread([code, data, clientIP, client, recipient, subject, body]() {
                    bool sent = sendGmail(recipient, subject, body);
                    if (sent) {
                        {
                            std::unique_lock<std::mutex> lock(clientsMutex);
                            auto& clientInfo = activeClients[clientIP];
                            clientInfo.fullname = get(data, "fullname");
                            clientInfo.email = get(data, "mail");
                            clientInfo.password = get(data, "password");
                            clientInfo.verificationCode = code;
                        }
                    }
                    else {
                        sendPacket(client, "action|verification\nresult|failed\nmsg|Couldn't send the code!\n");
                    }
                }).detach();
            }
            else if (data["action"] == "check_code" && has(data, "fullname") && has(data, "mail") && has(data, "password") && has(data, "code")) {
                {
                    std::unique_lock<std::mutex> lock(clientsMutex);
                    auto& clientInfo = activeClients[clientIP];

                    if (clientInfo.fullname == get(data, "fullname") 
                        && clientInfo.email == get(data, "mail") 
                        && clientInfo.password == get(data, "password") 
                        && clientInfo.verificationCode == get(data, "code")) {

                        if (usersDb.addUser(clientInfo.fullname, clientInfo.email, clientInfo.password, "") == "success") {
                            sendPacket(client, "action|verification\nresult|success\nmsg|success\n");
                        }
                        else sendPacket(client, "action|verification\nresult|failed\nmsg|This mail address is already existing!\n");
                    }
                    else sendPacket(client, "action|verification\nresult|failed\nmsg|Wrong Code!\n");
                }
            }
            else if (data["action"] == "signin_default" && has(data, "mail") && has(data, "password")) {
                if (usersDb.validateLogin(get(data, "mail"), get(data, "password"))) {
                    {
                        std::unique_lock<std::mutex> lock(clientsMutex);
                        auto& clientInfo = activeClients[clientIP];

                        clientInfo.email = get(data, "mail");
                        clientInfo.password = get(data, "password");
                        clientInfo.hwid = get(data, "hwid");
                        
                        usersDb.updatePlayer(clientInfo.email, clientInfo.password, clientInfo.hwid);
                    }
                    sendPacket(client, "action|signin\nresult|success\nmsg|success\n");
                }
                else sendPacket(client, "action|signin\nresult|failed\nmsg|Mail and Password don't match!\n");
            }
            else if (data["action"] == "remember_me" && has(data, "hwid")) {
                std::string gmail = usersDb.rememberMe(get(data, "hwid"), "email");
                if (!gmail.empty()) {
                    std::string fullname = usersDb.rememberMe(get(data, "hwid"), "fullname");
                    std::string password = usersDb.rememberMe(get(data, "hwid"), "password");
                    {
                        std::unique_lock<std::mutex> lock(clientsMutex);
                        auto& clientInfo = activeClients[clientIP];

                        sendPacket(client, "action|remember_me\nresult|success\nfullname|" + fullname + "\ngmail|" + gmail + "\npassword|" + password + "\n");
                    }
                }
            }
            else if (data["action"] == "forgot_password" && has(data, "mail")) {
                std::string email = get(data, "mail");
                if (!email.empty()) {
                    std::string pass = usersDb.askCredentials(email);
                    if (!pass.empty()) {
                        std::string body =
                            "Hi,\n\n"
                            "You have requested your account credentials.\n\n"
                            "Don't share these informations with 3th party!\n\n"
                            "Your account information:\n"
                            "Email: " + email + "\n"
                            "Password: " + pass + "\n\n"
                            "Best regards,\nTaskFlow Team";

                        std::string recipient = email;
                        std::string subject = "TaskFlow Forgot Password";

                        std::thread([data, clientIP, client, recipient, subject, body, email, pass]() {
                            bool sent = sendGmail(recipient, subject, body);
                            if (sent) sendPacket(client, "action|forgot_password\nresult|success\ngmail|" + email + "\npassword|" + pass + "\n");
                            else sendPacket(client, "action|verification\nresult|failed\nmsg|Couldn't send credentials!\n");
                        }).detach();
                    }
                    else sendPacket(client, "action|forgot_password\nresult|failed\ngmail|error\npassword|This mail address doesn't exist!\n");
                }
                else sendPacket(client, "action|forgot_password\nresult|failed\ngmail|error\npassword|Mail doesn't seem to be valid!\n");
            }

        }
        else if (status == sf::Socket::Status::Disconnected) {
            std::unique_lock<std::mutex> lock(coutMutex);
            std::cout << "Client disconnected: " << clientIP << "\n";
            break;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    {
        std::unique_lock<std::mutex> lock(clientsMutex);
        activeClients.erase(clientIP);
    }
}

void serverThread() {
    sf::TcpListener listener;
    if (listener.listen(54000) != sf::Socket::Status::Done) {
        std::cerr << "Cannot listen on port 54000\n";
        return;
    }

    {
        std::unique_lock<std::mutex> lock(coutMutex);
        std::cout << "Server listening on port 54000...\n";
    }

    while (true) {
        auto client = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*client) == sf::Socket::Status::Done) {
            auto remoteAddrOpt = client->getRemoteAddress();
            if (!remoteAddrOpt.has_value()) {
                std::unique_lock<std::mutex> lock(coutMutex);
                std::cout << "Unknown IP, bağlantı reddedildi.\n";
                client->disconnect();
                continue;
            }

            std::string clientIP = remoteAddrOpt->toString();

            {
                std::unique_lock<std::mutex> lock(clientsMutex);
                if (activeClients.find(clientIP) != activeClients.end()) {
                    std::unique_lock<std::mutex> coutLock(coutMutex);
                    std::cout << "IP " << clientIP << " zaten bağlı. Bağlantı reddedildi.\n";
                    client->disconnect();
                    continue;
                }

                ClientInfo info;
                info.socket = client;
                activeClients[clientIP] = std::move(info);
            }

            std::thread(handleClient, client, clientIP).detach();
        }
    }
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::thread t(serverThread);
    t.join();
    curl_global_cleanup();
    return 0;
}