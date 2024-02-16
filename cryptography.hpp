#pragma once

#include "fileHandling.hpp"

#include <iostream>
#include <string_view>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>


void SetPassword(std::string& password, std::vector<unsigned char>& key, std::vector<unsigned char>& iv);
void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
void CutHash(std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
bool DecryptAes(const std::vector<unsigned char>& encrypted, std::vector<unsigned char>& plain, const std::vector<unsigned char>& key, const std::vector<unsigned char>& iv);
