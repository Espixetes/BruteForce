#pragma once

#include <filesystem>
#include <fstream>
#include <vector>


namespace fs = std::filesystem;

void ReadFile(const fs::path& path, std::vector<unsigned char>& buf);
void WriteFile(const fs::path& path, const std::vector<unsigned char>& buf);
void AppendToFile(const fs::path& path, const std::vector<unsigned char>& buf);