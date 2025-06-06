#include "table.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>
#include <map>

#include "constants.hpp"

const std::map<std::string, Type> TypeMap{
  {"Integer", Type::Integer}
};

std::string readUntilChar(std::istream& is, char delimiter) {
  std::string str;
  std::getline(is, str, delimiter);
  return str;
}

Table::Table(std::string database, std::string tableName)
  :_databaseName(database), _tableName(tableName)
{
  std::ifstream ifs{DatabasesDirectory / _databaseName / (_tableName + FileExtension)};
  {
    std::string headers;
    std::getline(ifs, headers);
    std::istringstream iss{headers};
    this->_headers = this->_readHeaders(iss);
  }
  {
    std::string row;
    while (std::getline(ifs, row)) {
      std::istringstream iss{row};
      this->_rows.push_back (this->_getRow(iss));
    }
  }


  for (auto l : this->_rows) {
    for (auto x : l) {
      std::cout << std::get<int>(x) << ",";
    }
    std::cout << "\n";
  }
}

Table::~Table() { }

Header Table::_getHeader(std::istream& is) {
  std::string HeaderName = readUntilChar(is, TypeOpener);
  if (HeaderName.empty()) {
    throw std::runtime_error("Error Parsing Header Name in '" + _databaseName + "." + _tableName + "' Table\n");
  }

  std::string HeaderTypeStr = readUntilChar(is, TypeCloser);
  if (HeaderTypeStr.empty()) {
    throw std::runtime_error("Error Parsing Header Type For '" + HeaderName + 
                             "' In '" + _databaseName + "." + _tableName + "' Table\n");
  }

  Type HeaderType;
  try {
    HeaderType = TypeMap.at(HeaderTypeStr);
  }
  catch (const std::out_of_range& e) {
    throw std::runtime_error("Error Converting Header Type For '" + HeaderName + 
                             "' In '" + _databaseName + "." + _tableName + "' Table\n");
  }
  return {HeaderType, HeaderName};
}

std::vector<Header> Table::_readHeaders(std::istream& is) {
  std::vector<Header> headers;

  headers.push_back(this->_getHeader(is));

  char ch;
  while (is >> ch) {
    if (ch == FieldDelimiter) {
      headers.push_back(this->_getHeader(is));
    } 
    else {
      is.unget();
      break;
    }
  }

  return headers;
}

std::vector<fieldType> Table::_getRow(std::istream& is) {
  std::vector<fieldType> row;
  for (unsigned int currentIndex = 0; currentIndex < this->_headers.size(); ++currentIndex) {
    std::string fieldValue = readUntilChar(is, FieldDelimiter);
    switch (this->_headers[currentIndex].type) {
      case Type::Integer:
        row.push_back(std::stoi(fieldValue));
        break;
      default:
        throw std::runtime_error("Error parsing field " + std::to_string(currentIndex) +
                                 " in table " + _databaseName + "." + _tableName +
                                 ": unsupported type or invalid value '" + fieldValue + "'");
    }
  }
  return row;
}
