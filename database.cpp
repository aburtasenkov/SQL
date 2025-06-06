#include "database.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "constants.hpp"

Database::Database(std::string databaseName)
  :_databaseName(databaseName)
{
  if (!std::filesystem::exists(DatabasesDirectory)) {
    std::filesystem::create_directory(DatabasesDirectory);
    std::cout << "Database Directory Does Not Exist Yet...\n"
              << "Database Directory Created.\n";
  }

  if (!std::filesystem::exists(DatabasesDirectory / databaseName)) {
    std::filesystem::create_directory(DatabasesDirectory / databaseName);
    std::cout << "Database '" << databaseName << "' Was Created.\n";
    return;
  }

  for (auto const& dirEntry : std::filesystem::directory_iterator{DatabasesDirectory / _databaseName}) {
    _tables.push_back(dirEntry.path().stem());
  }
}

Database::~Database() {}

void Database::createTable(std::string tableName) {
  if (std::find(_tables.begin(), _tables.end(), tableName) != _tables.end()) {
    std::cout << "Table '" << tableName << "' Already Exists.\n";
    return;
  }

  std::ofstream ofs {DatabasesDirectory / _databaseName / (tableName + FileExtension)};
  std::cout << "Table '" << tableName << "' Was Created.\n";
}
