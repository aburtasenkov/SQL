#include "logic.hpp"

#include <iostream>
#include <filesystem>

#include "source/constant.hpp"
#include "source/token.hpp"
#include "source/database.hpp"

DB::Database currentDatabase;

void create(std::istream& is)
// SQL Create Operation
{
  SQL::Object obj;
  Token::operator>>(is, obj);
  switch (obj) {
    case SQL::Object::None: 
      std::cerr << "create::BadSyntaxError\n";
      break;
    case SQL::Object::Table:
    {
      createTable(is);
      break;
    }
    case SQL::Object::Database:
      createDatabase(is);
      break;
  }
}

void createTable(std::istream& is)
// Create Table 
{
  is.ignore(1); // Skip Whiteline Character Delimiting TABLE keyword and Table's Name
  std::string tableName = Token::readUntilChar(is, Constant::ParameterOpener);

  // Check if Table Already Exists
  if (currentDatabase.tableExists(tableName)) {
    Token::readUntilChar(is, Constant::ParameterCloser); // Skip All The Parameters
    throw std::runtime_error("Error Creating Table '" + tableName + "' In '" 
                          + currentDatabase.name() + "' Database. '" + tableName + "' Already Exists.\n");
  }

  std::string parameters = Token::readUntilChar(is, Constant::ParameterCloser);

  std::istringstream iss{parameters};
  std::vector<TBL::Header> headers = TBL::Table::readHeaders(iss, currentDatabase.name(), tableName);

  TBL::Table tbl{currentDatabase.name(), tableName, headers};
}

/*
SYNTAX FOR TABLE CREATION
CREATE TABLE tableName (FIELD DATATYPE, FIELD DATATYPE)
*/

DB::Database createDatabase(std::istream& is)
// Create New Database
{
  std::string databaseName = Token::getToken(is);
  return DB::Database(databaseName);
}

void useDatabase(std::istream& is) 
// Change Current Database in Use
{
  std::string databaseName = Token::getToken(is);
  currentDatabase = DB::Database(databaseName);
  std::cout << "Using database " << databaseName << ".\n";
}