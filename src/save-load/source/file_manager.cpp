#include "../headers/file_manager.h"

FileManager::FileManager(const std::string &name) : filename(name) {}

FileManager::~FileManager() {}

void FileManager::read(json &jsn)
{
    std::ifstream input_file(filename);
    if(!input_file.is_open())
    {
        throw std::runtime_error("Couldn't open file for reading.");
    }

    std::string hash;
    std::getline(input_file, hash);
    std::string data;
    std::getline(input_file, data);

    input_file.close();

    if(sha256(data) != hash)
    {
        throw SaveFileDamagedException("Seems like file was damaged.");
    }

    jsn = json::parse(data);
}

void FileManager::write(const json &jsn)
{
    std::string data = jsn.dump();
    std::string hash = sha256(data);

    std::ofstream output_file(filename);
    if(!output_file.is_open())
    {
        throw std::runtime_error("Couldn't open file for writing.");
    }

    output_file << hash << std::endl << data;
    output_file.close();
}

std::string FileManager::sha256(const std::string &str)
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, str.c_str(), str.size());
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for(unsigned int i = 0; i < hash_len; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
