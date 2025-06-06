#pragma once 

#include <string>
#include <vector>

#include "table.hpp"

class Database {
public:
  Database(std::string);
  ~Database();

  void createTable(std::string);
private:
  std::string _databaseName;
  std::vector<std::string> _tables;
};
