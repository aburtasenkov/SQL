#pragma once 

#include <string>
#include <vector>

#include "table.hpp"

namespace DB{
  class Database {
    public:
    Database();
    Database(std::string);
    ~Database();
    
    bool tableExists(std::string);
    
    const std::string& name();
    private:
    std::string _databaseName;
    std::vector<std::string> _tables; // Vector of All Tables (Not Including the File Extension)
  };
};
