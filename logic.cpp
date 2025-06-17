#include <iostream>
#include <filesystem>

#include "logic.hpp"
#include "constants.hpp"
#include "token.hpp"
#include "database.hpp"

Database currentDatabase;

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
    {
      createTable(is);
      break;
    }
    case Object::Database:
      createDatabase(is);
      break;
  }
}

void createTable(std::istream& is)
// Create Table 
{
  is.ignore(1); // Skip Whiteline Character Delimiting TABLE keyword and Table's Name
  std::string tableName = readUntilChar(is, ParameterOpener);

  // Check if Table Already Exists
  if (currentDatabase.tableExists(tableName)) {
    readUntilChar(is, ParameterCloser); // Skip All The Parameters
    throw std::runtime_error("Error Creating Table '" + tableName + "' In '" 
                          + currentDatabase.name() + "' Database. '" + tableName + "' Already Exists.\n");
  }

  std::string parameters = readUntilChar(is, ParameterCloser);

  std::istringstream iss{parameters};
  std::vector<Header> headers = Table::readHeaders(iss, currentDatabase.name(), tableName);

  Table tbl{currentDatabase.name(), tableName, headers};
}

/*
SYNTAX FOR TABLE CREATION
CREATE TABLE tableName (FIELD DATATYPE, FIELD DATATYPE)
*/

Database createDatabase(std::istream& is)
// Create New Database
{
  std::string databaseName = getToken(is);
  return Database(databaseName);
}

void useDatabase(std::istream& is) 
// Change Current Database in Use
{
  std::string databaseName = getToken(is);
  currentDatabase = Database(databaseName);
  std::cout << "Using database " << databaseName << ".\n";
}