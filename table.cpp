#include "table.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>
#include <map>

#include "constants.hpp"

const std::map<std::string, Type> TypeMapEnum{
  {"Integer", Type::Integer}
};

const std::map<Type, std::string> TypeMapString {
  {Type::Integer, "Integer"}
};

Table::Table(std::string database, std::string tableName)
  :_databaseName(database), _tableName(tableName)
{
  // Read Headers
  std::ifstream ifs{DatabasesDirectory / this->_databaseName / (this->_tableName + FileExtension)};
  {
    std::string headers;
    std::getline(ifs, headers);
    std::istringstream iss{headers};
    this->_headers = this->_readHeaders(iss);
  }
  // Read Rows
  {
    std::string row;
    while (std::getline(ifs, row)) {
      std::istringstream iss{row};
      this->_rows.push_back (this->_getRow(iss));
    }
  }
}

Table::~Table() {
  std::ofstream ofs{DatabasesDirectory / this->_databaseName / (this->_tableName + FileExtension)};

  // Log Headers
  for (unsigned int i = 0; i < this->_headers.size(); ++i) {
    const Header& header = this->_headers[i];
    ofs << header.name << TypeOpener << TypeMapString.at(header.type) << TypeCloser;
    if (i != this->_headers.size() - 1) ofs << FieldDelimiter;
  }
  ofs << "\n";

  // Log Rows
  for (const auto& row : this->_rows) {
    for (unsigned int i = 0; i < row.size(); ++i) {
      switch (this->_headers[i].type)
      {
      case Type::Integer:
        ofs << std::get<int>(row[i]) << FieldDelimiter; 
        break;
      }
    }
    ofs << "\n";
  }
}

Header Table::_getHeader(std::istream& is) 
// Return 1 Header of Header Line
{
  std::string HeaderName = readUntilChar(is, TypeOpener);
  if (HeaderName.empty()) {
    throw std::runtime_error("Error Parsing Header Name in '" + this->_databaseName + "." + this->_tableName + "' Table\n");
  }

  std::string HeaderTypeStr = readUntilChar(is, TypeCloser);
  if (HeaderTypeStr.empty()) {
    throw std::runtime_error("Error Parsing Header Type For '" + HeaderName + 
                             "' In '" + this->_databaseName + "." + this->_tableName + "' Table\n");
  }

  Type HeaderType;
  try {
    HeaderType = TypeMapEnum.at(HeaderTypeStr);
  }
  catch (const std::out_of_range& e) {
    throw std::runtime_error("Error Converting Header Type For '" + HeaderName + 
                             "' In '" + this->_databaseName + "." + this->_tableName + "' Table\n");
  }
  return {HeaderType, HeaderName};
}

std::vector<Header> Table::_readHeaders(std::istream& is) 
// Create Vector of All Headers of a Line
{
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

std::vector<fieldType> Table::_getRow(std::istream& is) 
// Create Data From 1 Row
{
  std::vector<fieldType> row;
  for (unsigned int currentIndex = 0; currentIndex < this->_headers.size(); ++currentIndex) {
    std::string fieldValue = readUntilChar(is, FieldDelimiter);
    switch (this->_headers[currentIndex].type) {
      case Type::Integer:
        row.push_back(std::stoi(fieldValue));
        break;
      default:
        throw std::runtime_error("Error parsing field #" + std::to_string(currentIndex) +
                                 " in table " + this->_databaseName + "." + this->_tableName +
                                 ": unsupported type or invalid value '" + fieldValue + "'");
    }
  }
  return row;
}
