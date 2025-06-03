#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <exception>
#include <filesystem>

#include "token.hpp"

const std::filesystem::path DatabasesDirectory = "databases";
std::filesystem::path currentDatabase;

enum class Operator : unsigned char {
  None, Create, Use
};

enum class Object : unsigned char {
  None, Table, Database
};

std::map<std::string, Operator> OperatorMap {
  {"create", Operator::Create},
  {"use", Operator::Use}
};

std::map<std::string, Object> ObjectMap {
  {"table", Object::Table}, 
  {"database", Object::Database}
};

template <typename T>
T getMapValue(std::istream& is, const std::map<std::string, T>& map) {
  std::string token = getToken(is);
  try {
    return map.at(token);
  }
  catch (const std::out_of_range& e) {
    return T::None;
  }
}

std::istream& operator>>(std::istream& is, Operator& op) {
  op = getMapValue(is, OperatorMap);
  return is;
}

std::istream& operator>>(std::istream& is, Object& obj) {
  obj = getMapValue(is, ObjectMap);
  return is;
}

void createTable(std::istream& is) {
  if (currentDatabase == "") throw std::runtime_error("createTable::MissingDatabaseError");
  std::string tableName = getToken(is);
  std::cout << "Creating table " << tableName << "...\n";
}

void createDatabase(std::istream& is) {
  std::string databaseName = getToken(is);
  if (std::filesystem::exists(DatabasesDirectory/databaseName)) throw std::runtime_error("createDatabase::DatabaseAlreadyExistsError");
  std::filesystem::create_directory(DatabasesDirectory/databaseName);
  std::cout << "Database " << databaseName << " created.\n";
}

void create(std::istream& is) {
  Object obj;
  is >> obj;
  switch (obj) {
    case Object::None: 
      std::cerr << "create::BadSyntaxError\n";
      break;
    case Object::Table:
      createTable(is);
      break;
    case Object::Database:
      createDatabase(is);
      break;
  }
}

void useDatabase(std::istream& is) {
  std::string databaseName = getToken(is);
  if (!std::filesystem::exists(DatabasesDirectory/databaseName)) throw std::runtime_error("useDatabase::MissingDatabaseError");
  currentDatabase = databaseName;
  std::cout << "Using database " << currentDatabase << ".\n";
}

void initialSetup() {
  if (!std::filesystem::exists(DatabasesDirectory)) {
    std::filesystem::create_directory(DatabasesDirectory);
    std::cout << "Database Directory Created.\n";
  }
}

int main(int argc, char ** argv) {
  initialSetup();

  std::istringstream is {argumentsToString(argc, argv)};
  Operator op;
  while (is >> op) {
    try {
      switch (op) {
        case Operator::None:
          std::cerr << "main::BadSyntaxError\n";
          break;
        case Operator::Create:
          create(is);
          break;
        case Operator::Use:
          useDatabase(is);
          break;
      }
    }
    catch (const std::runtime_error& e) {
      std::cerr << e.what() << "\n";
      exit(1);
    }
  }
  return 0;
}