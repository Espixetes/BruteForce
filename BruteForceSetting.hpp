#pragma once
#include "cryptography.hpp"
#include <thread>


class BruteForceSetting
{
public:
	std::string GetAvailableSymbol() const;
	int GetAmountCPU() const;
	fs::path GetEncryptedFilePath() const;
	void SetAmountCPU();
	void SetEncryptedFilePath(std::filesystem::path encyptedPass);
private:
	int m_amountOfCPUCores;
	std::string m_availableSymbol = "abcdefghijklmnopqrstuvwxyz0123456789";
	fs::path m_encryptedFile;
};