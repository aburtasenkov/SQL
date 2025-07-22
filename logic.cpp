#include "logic.hpp"

#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <string>

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
      throw std::runtime_error("create::BadSyntaxError");
    case SQL::Object::Table:
    {
      createTable(is);
      break;
    }
    case SQL::Object::Database:
      currentDatabase = createDatabase(is);
      break;
  }
}

TBL::Table createTable(std::istream& is)
// Create Table 
{
  is.ignore(1); // Skip Whiteline Character Delimiting TABLE keyword and Table's Name
  std::string tableName = Token::readUntilChar(is, Constant::ParameterOpener);

  if (currentDatabase.tableExists(tableName)) {
    Token::readUntilChar(is, Constant::ParameterCloser); // Skip All The Parameters
    throw std::runtime_error("Error Creating Table '" + tableName + "' In '" 
                          + currentDatabase.name() + "' Database. '" + tableName + "' Already Exists.\n");
  }

  std::string parameters = Token::readUntilChar(is, Constant::ParameterCloser);

  std::istringstream iss{parameters};
  std::vector<TBL::Header> headers = TBL::Table::readHeaders(iss, currentDatabase.name(), tableName);

  TBL::Table table{currentDatabase.name(), tableName, headers};
  std::cout << "Table '" + currentDatabase.name() + "." + tableName + "' Was Created.\n";

  return table;
}

/*
SYNTAX FOR TABLE CREATION
CREATE TABLE tableName (FIELD DATATYPE, FIELD DATATYPE)
*/

void insert(std::istream& is) 
// SQL insert command
{
  SQL::Keyword keyword;
  Token::operator>>(is, keyword);
  switch (keyword)
  {
  case SQL::Keyword::None:
    throw std::runtime_error("insert::BadSyntaxError");
  case SQL::Keyword::Into:
    insertInto(is);
    break;
  }
}

void insertInto(std::istream& is) {
  // Read current table
  std::string tableName;
  is >> tableName;
  TBL::Table table{currentDatabase.name(), tableName};

  // skip values keyword
  {
    SQL::Keyword values;
    Token::operator>>(is, values);
    if (values != SQL::Keyword::Values) throw std::runtime_error("insertInto::BadInput");
  }

  // insert data
  Token::readUntilChar(is, Constant::ParameterOpener);
  std::istringstream iss{Token::readUntilChar(is, Constant::ParameterCloser)};
  std::vector<TBL::fieldType> entry = table.createRow(iss);
  table.insert(entry);
}

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