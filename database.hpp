#pragma once 

#include <string>
#include <vector>

#include "table.hpp"

class Database {
public:
  Database();
  Database(std::string);
  ~Database();

  void createTable(std::string);

  const std::string& name();
private:
  std::string _databaseName;
  std::vector<std::string> _tables; // Vector of All Tables (Not Including the File Extension)
};
