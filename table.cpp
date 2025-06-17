#include "table.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>

#include "constants.hpp"
#include "token.hpp"

Table::Table(std::string databaseName, std::string tableName, std::vector<Header> headers)
  :_databaseName(databaseName), _tableName(tableName), _headers(headers)
// Initializer for Creating New Tables
{ }

Table::Table(std::string databaseName, std::string tableName)
  :_databaseName(databaseName), _tableName(tableName)
// Initializer for Existing Tables
{
  // Read Headers
  std::ifstream ifs{DatabasesDirectory / this->_databaseName / (this->_tableName + FileExtension)};
  {
    std::string headers;
    std::getline(ifs, headers);
    std::istringstream iss{headers};
    this->_headers = this->readHeaders(iss, this->_databaseName, this->_tableName);
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
    ofs << header.name << " " << TypeMapString.at(header.type) << FieldDelimiter << " ";
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

std::vector<Header> Table::readHeaders(std::istream& is, const std::string databaseName, const std::string tableName) 
// Create Vector of All Headers of a Line
{
  std::vector<Header> headers;

  std::string headerName, headerTypeStr;
  while (is >> headerName >> headerTypeStr) {
    transformString(headerTypeStr, std::tolower);
    // Strip Trailing Comma if Present
    if (!headerTypeStr.empty() && headerTypeStr.back() == ',') headerTypeStr.pop_back();
  
    Type headerType;
    try {
      headerType = TypeMapEnum.at(headerTypeStr);
    } 
    catch (const std::out_of_range& e) {
      throw std::runtime_error("Unknown Type '" + headerTypeStr + "' For Header '" + headerName + 
                               "' In '" + databaseName + "." + tableName + "' Table\n");
    }
    headers.push_back({headerType, headerName});
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
