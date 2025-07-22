#include "database.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "constant.hpp"

DB::Database::Database() {
  // If Database Directory Does Not Exist Yet - Create It 
  if (!std::filesystem::exists(Constant::DatabasesDirectory)) {
    std::filesystem::create_directory(Constant::DatabasesDirectory);
    std::cout << "Database Directory Does Not Exist Yet...\n"
              << "Database Directory Created.\n";
  }
}

DB::Database::Database(std::string databaseName)
  :Database()
{
  this->_databaseName = databaseName;
  // If Database Does Not Exist Yet - Create It and Return
  if (!std::filesystem::exists(Constant::DatabasesDirectory / databaseName)) {
    std::filesystem::create_directory(Constant::DatabasesDirectory / databaseName);
    std::cout << "Database '" << databaseName << "' Was Created.\n";
    return;
  }
  
  // Code For Existing Databases
  // Read All Tables
  for (const auto& dirEntry : std::filesystem::directory_iterator{Constant::DatabasesDirectory / this->_databaseName}) {
    this->_tables.emplace_back(dirEntry.path().stem());
  }
}

DB::Database::~Database() {}

bool DB::Database::tableExists(std::string tableName) {
  if (std::find(this->_tables.begin(), this->_tables.end(), tableName) != this->_tables.end()) {
    return true;
  }
  return false;
}

const std::string& DB::Database::name() {
  return _databaseName;
}
