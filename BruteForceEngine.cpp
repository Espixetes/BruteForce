#include "BruteForceEngine.hpp"

void bruteforce::Bruteforce::Start(std::string encryptedFile)   //Calculate number of passwords for each thread , create thread
{
    m_setting.SetEncryptedFilePath(encryptedFile);
    m_encryptedFile = m_setting.GetEncryptedFilePath();

    m_setting.SetAmountCPU();

    ReadFile(m_encryptedFile, m_encryptedText);
    CutHash(m_encryptedText, m_correctHash);
    m_correctHash.resize(SHA256_DIGEST_LENGTH);

    std::vector<std::jthread> threads;
    int step = std::ceil(static_cast<double>(AmountPassword()) / m_setting.GetAmountCPU());
    int start = 0;
    int end = 0;
    for (int i = 0; i < m_setting.GetAmountCPU(); ++i)
    {
        start = end;
        end += step;
        if (end > AmountPassword())
        {
            end = AmountPassword();
        }

        threads.push_back(std::jthread(&Bruteforce::BruteForce, this, start, end));
    }
    for (auto& thread : threads)
    {
        thread.join();
    }

    if (!m_password.empty())
    {
        Decrypt();
        std::cout << "Password: " << m_password << std::endl;
    }
    else
        std::cout << "Password not found" << std::endl;
    {
    }
}


std::vector<std::string> bruteforce::Bruteforce::PassPack(int start, int end)
{
    std::vector<std::string> pack{};
    for (uint64_t i = start; i < end; ++i)
    {
        if (!m_passwordNotFound.test())
        {
        std::string password = GeneratePassword(i);
        pack.push_back(password);
        }
        else
        {
            return pack;
        }
    }
    return pack;
}


void bruteforce::Bruteforce::BruteForce(int start, int end)    //Generate passwords causes passwords to be written and decrypts the file
{
    try
    {
    std::ofstream log(m_logFile, std::ios::app);
        if (m_logFile.empty())
        {
            std::exception err ("Could not open file");
            throw err;
        }
        if (!log.is_open())
        {
            throw "Could not open file" ;
 
        }
    std::vector<std::string> pack = PassPack(start, end);
    for (uint32_t i = 0; i < pack.size(); ++i)
    {
        m_mutex.lock();
        ++m_checkedPasswordsAmount;
        log.write(&pack[i][0], pack[i].length());
        log << '\n';
        m_mutex.unlock();

        std::vector<unsigned char> key(EVP_MAX_KEY_LENGTH);
        std::vector<unsigned char> iv(EVP_MAX_IV_LENGTH);
        std::vector<unsigned char> plainText{};

        SetPassword(pack[i], key, iv);
        if (DecryptAes(m_encryptedText, plainText, key, iv))
        {
            std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
            CalculateHash(plainText, hash);
            if (m_correctHash == hash)
            {
                m_password = pack[i];
                m_passwordIsFound = true;
                break;
            }
        }

    }
    }
    catch (std::exception& error)
    {
        std::cerr << error.what();
    }
    catch (...)
    {
        std::cerr << "Unknown Error";
    }
}


int bruteforce::Bruteforce::AmountPassword()   // Calculate all possible password
{
    int amountPassword = 0;
    for (int i = m_length; i > 0; --i)
    {
        amountPassword += std::pow(m_availableSymbol.size(), i);
    }
    return amountPassword;
}

std::string bruteforce::Bruteforce::GeneratePassword(uint64_t index)   //Generete Password from  the transmitted sequence numbers
{
    int length{};
    uint64_t counter{};
    if (index)
    {
        do
        {
            ++length;
            counter += std::pow(m_availableSymbol.size(), length);
            if (length == 1)
            {
                --counter;
            }
        } while (counter < index);
    }
    else
    {
        length = 1;
    }
    std::string password{};
    counter = index;
    for (int i = 1; i < length; ++i)
    {
        counter -= std::powl(m_availableSymbol.size(), i);
    }
    for (int i = 0; i < length; ++i)
    {
        uint64_t ch = counter % m_availableSymbol.size();
        password = m_availableSymbol[ch] + password;
        counter /= m_availableSymbol.size();
    }
    return password;
}


void bruteforce::Bruteforce::Decrypt() //Sets the password and decrypts
{
    std::vector<unsigned char> key(EVP_MAX_KEY_LENGTH);
    std::vector<unsigned char> iv(EVP_MAX_IV_LENGTH);
    SetPassword(m_password, key, iv);
    DecryptAes(m_encryptedText, m_plainText, key, iv);
    WriteFile(m_plainFile, m_plainText);
}