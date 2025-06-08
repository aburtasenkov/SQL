#include "database.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "constants.hpp"

Database::Database(std::string databaseName)
  :_databaseName(databaseName)
{
  // If Database Directory Does Not Exist Yet - Create It 
  if (!std::filesystem::exists(DatabasesDirectory)) {
    std::filesystem::create_directory(DatabasesDirectory);
    std::cout << "Database Directory Does Not Exist Yet...\n"
              << "Database Directory Created.\n";
  }

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

void Database::createTable(std::string tableName) {
  // If Already Exists - Nothing to Create
  if (std::find(this->_tables.begin(), this->_tables.end(), tableName) != this->_tables.end()) {
    std::cout << "Table '" << tableName << "' Already Exists.\n";
    return;
  }

  // TODO - Initializer List for Fields
  std::ofstream ofs {DatabasesDirectory / this->_databaseName / (tableName + FileExtension)};
  std::cout << "Table '" << tableName << "' Was Created.\n";
}
