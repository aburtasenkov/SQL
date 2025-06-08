#include <iostream>
#include <filesystem>

#include "logic.hpp"
#include "constants.hpp"
#include "token.hpp"
#include "database.hpp"

// Database currentDatabase;

void create(std::istream& is)
// SQL Create Operation
{
  Object obj;
  is >> obj;
  switch (obj) {
    case Object::None: 
      std::cerr << "create::BadSyntaxError\n";
      break;
    case Object::Table:
      // TODO CREATE TABLE
      break;
    case Object::Database:
      createDatabase(is);
      break;
  }
}

Database createDatabase(std::istream& is)
// Create New Database
{
  std::string databaseName = getToken(is);
  return Database(databaseName);
}

void useDatabase(std::istream& is) 
// Change Current Database in Use
{
  // TODO USE DATABASE
  // std::string databaseName = getToken(is);
  // if (!std::filesystem::exists(DatabasesDirectory/databaseName)) throw std::runtime_error("useDatabase::MissingDatabaseError");
  // currentDatabase = databaseName;
  // std::cout << "Using database " << currentDatabase << ".\n";
}