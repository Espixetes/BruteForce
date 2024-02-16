#include "BruteForceSetting.hpp"

void BruteForceSetting::SetAmountCPU()
{
	m_amountOfCPUCores = std::jthread::hardware_concurrency();
}

void BruteForceSetting::SetEncryptedFilePath(std::filesystem::path encyptedPass)
{
	m_encryptedFile = encyptedPass;
}

int BruteForceSetting::GetAmountCPU() const
{
	return m_amountOfCPUCores;
}

std::string BruteForceSetting::GetAvailableSymbol() const
{
	return m_availableSymbol;
}

fs::path BruteForceSetting::GetEncryptedFilePath() const
{
	return m_encryptedFile;
}