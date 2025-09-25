#pragma once
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <sqlite_modern_cpp.h>

#include <string>
#include <iostream>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

class UsersBase {
private:
    sqlite::database db;

    std::string base64Encode(const std::string& in) {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new(BIO_s_mem());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        b64 = BIO_push(b64, bmem);

        BIO_write(b64, in.data(), (int)in.size());
        BIO_flush(b64);

        BUF_MEM* bptr;
        BIO_get_mem_ptr(b64, &bptr);
        std::string out(bptr->data, bptr->length);

        BIO_free_all(b64);
        return out;
    }

    std::string base64Decode(const std::string& in) {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new_mem_buf(in.data(), (int)in.size());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        bmem = BIO_push(b64, bmem);

        std::vector<char> buf(in.size());
        int decoded = BIO_read(bmem, buf.data(), (int)buf.size());
        if (decoded < 0) {
            BIO_free_all(bmem);
            throw std::runtime_error("Base64 decode failed");
        }
        BIO_free_all(bmem);
        return std::string(buf.data(), decoded);
    }

public:
    UsersBase(const std::string& dbPath) : db(dbPath) {
        try {
            db << "CREATE TABLE IF NOT EXISTS UsersBase ("
                "fullname TEXT,"
                "email TEXT PRIMARY KEY,"
                "password TEXT,"
                "hwid TEXT);";
        }
        catch (const std::exception& e) {
            std::cerr << "DB initialization error: " << e.what() << std::endl;
        }
    }

    std::string addUser(const std::string& fullname,
        const std::string& email,
        const std::string& password,
        const std::string& hwid)
    {
        try {
            int count1 = 0, count2 = 0;
            db << "SELECT COUNT(*) FROM UsersBase WHERE email = ?;"
                << email
                >> count1;
            if (count1 > 0) return "Error: There is already an account with this mail!";

            db << "SELECT COUNT(*) FROM UsersBase WHERE hwid = ?;"
                << hwid
                >> count2;
            if (count2 > 0) return "Error: You have already created an accoun from this pc!";


            std::string hashedPassword = base64Encode(password);

            db << "INSERT INTO UsersBase (fullname, email, password, hwid) VALUES (?, ?, ?, ?);"
                << fullname
                << email
                << hashedPassword
                << hwid;

            return "success";
        }
        catch (const std::exception& e) {
            std::cerr << "Add user error: " << e.what() << std::endl;
            return "Error: unknown";
        }
    }

    bool updatePlayer(const std::string& email,
        const std::string& newPassword,
        const std::string& newHwid)
    {
        try {
            std::string hashedPassword = base64Encode(newPassword);
            db << "UPDATE UsersBase SET password = ?, hwid = ? WHERE email = ?;"
                << hashedPassword
                << newHwid
                << email;
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << "Update user error: " << e.what() << std::endl;
            return false;
        }
    }

    bool validateLogin(const std::string& email, const std::string& password) {
        try {
            std::string hashedPassword = base64Encode(password);
            int count = 0;
            db << "SELECT COUNT(*) FROM UsersBase WHERE email = ? AND password = ?;"
                << email
                << hashedPassword
                >> count;
            return count > 0;
        }
        catch (const std::exception& e) {
            std::cerr << "Login validation error: " << e.what() << std::endl;
            return false;
        }
    }

    std::string rememberMe(const std::string& hwid, const std::string& key) {
        try {
            std::string pulledData;
            bool found = false;

            db << "SELECT " + key + " FROM UsersBase WHERE hwid = ?;"
                << hwid
                >> [&](std::string value) {
                pulledData = value;
                found = true;
            };

            if (found) return pulledData;
            return "";
        }
        catch (const std::exception& e) {
            std::cerr << "Login validation error: " << e.what() << std::endl;
            return "";
        }
    }

    std::string askCredentials(const std::string& email) {
        try {
            std::string pulledData;
            bool found = false;

            db << "SELECT password FROM UsersBase WHERE email = ?;"
                << email
                >> [&](std::string value) {
                pulledData = value;
                found = true;
            };

            if (found) return base64Decode(pulledData);
            return "";
        }
        catch (const std::exception& e) {
            std::cerr << "Login validation error: " << e.what() << std::endl;
            return "";
        }
    }

    void readAll() {
        try {
            db << "SELECT fullname, email, password, hwid FROM UsersBase;"
                >> [&](std::string fullname, std::string email, std::string password, std::string hwid) {
                std::cout << "Fullname: " << fullname
                    << " | Email: " << email
                    << " | Password: " << password
                    << " | HWID: " << hwid
                    << std::endl;
                };
        }
        catch (const std::exception& e) {
            std::cerr << "ReadAll error: " << e.what() << std::endl;
        }
    }

};