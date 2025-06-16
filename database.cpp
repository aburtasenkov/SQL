#include "database.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "constants.hpp"

Database::Database() {
  // If Database Directory Does Not Exist Yet - Create It 
  if (!std::filesystem::exists(DatabasesDirectory)) {
    std::filesystem::create_directory(DatabasesDirectory);
    std::cout << "Database Directory Does Not Exist Yet...\n"
              << "Database Directory Created.\n";
  }
}

Database::Database(std::string databaseName)
  :Database()
{
  this->_databaseName = databaseName;
  // If Database Does Not Exist Yet - Create It and Return
  if (!std::filesystem::exists(DatabasesDirectory / databaseName)) {
    std::filesystem::create_directory(DatabasesDirectory / databaseName);
    std::cout << "Database '" << databaseName << "' Was Created.\n";
    return;
  }
  
  // Code For Existing Databases
  // Read All Tables
  for (const auto& dirEntry : std::filesystem::directory_iterator{DatabasesDirectory / this->_databaseName}) {
    this->_tables.push_back(dirEntry.path().stem());
  }
}

Database::~Database() {}

bool Database::tableExists(std::string tableName) {
  if (std::find(this->_tables.begin(), this->_tables.end(), tableName) != this->_tables.end()) {
    std::cout << "Table '" << tableName << "' Already Exists.\n";
    return true;
  }
  return false;
}

const std::string& Database::name() {
  return _databaseName;
}
