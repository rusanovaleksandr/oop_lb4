#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../../exceptions/headers/save_file_damaged_exception.h"

using json = nlohmann::json;

class FileManager
{
    std::string filename;

    std::string sha256(const std::string &str);

public:
    FileManager(const std::string &name);
    void read(json &jsn);
    void write(const json &jsn);
    ~FileManager();
};


#endif
