#include "fileHandling.hpp"

void ReadFile(const fs::path& path, std::vector<unsigned char>& buf)
{
	std::basic_fstream<unsigned char> file(path, std::ios::binary | std::fstream::in);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file");
	}
	buf.clear();
	buf.insert(buf.begin(), std::istreambuf_iterator<unsigned char>(file), std::istreambuf_iterator<unsigned char>());
}

void WriteFile(const fs::path& path, const std::vector<unsigned char>& buf)
{
	std::basic_ofstream<unsigned char> file(path, std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file");
	}
	file.write(&buf[0], buf.size());
}

void AppendToFile(const fs::path& path, const std::vector<unsigned char>& buf)
{
	std::basic_ofstream<unsigned char> file(path, std::ios::binary | std::ios::app);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file");
	}
	file.write(&buf[0], buf.size());
}