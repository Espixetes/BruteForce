#pragma once

#include "BruteForceSetting.hpp"

#include <string>
#include <cmath>
#include <windows.h>
#include <mutex>
#include <memory>
#include <exception>
#include <unordered_map>

namespace bruteforce
{
    class BruteForceEngine
    {
    public:
        void Start(const std::string& encryptedFile);
    private:
        void BruteForce(int start, int end);
        int AmountPassword();
        std::vector< std::string> PassPack(int start, int end);
        std::string GeneratePassword(uint64_t index);
        void Decrypt();
    private:
        std::atomic_flag m_passwordNotFound = ATOMIC_FLAG_INIT;
        BruteForceSetting m_setting;
        std::mutex m_mutex;
        int m_length = 4;
        std::string m_pass;
        std::vector<unsigned char> m_encryptedText;
        std::vector<unsigned char> m_plainText;
        std::vector<unsigned char> m_correctHash;
        std::string m_password;
        fs::path m_plainFile = "plain_text_brute_force.txt";
        fs::path m_logFile = "passwords.txt";
        fs::path m_encryptedFile;
        int64_t m_checkedPasswordsAmount = 0;
        bool m_passwordIsFound = false;
        std::string m_availableSymbol = m_setting.GetAvailableSymbol();
    };
}