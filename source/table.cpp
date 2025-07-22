#include "table.hpp"

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>

#include "constant.hpp"
#include "token.hpp"

TBL::Table::Table(std::string databaseName, std::string tableName, std::vector<Header> headers)
  :_databaseName(databaseName), _tableName(tableName), _headers(headers)
// Initializer for Creating New Tables
{ }

TBL::Table::Table(std::string databaseName, std::string tableName)
  :_databaseName(databaseName), _tableName(tableName)
// Initializer for Existing Tables
{
  // Read Headers
  std::ifstream ifs{Constant::DatabasesDirectory / this->_databaseName / (this->_tableName + Constant::FileExtension)};
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
      this->_rows.push_back(this->createRow(iss));
    }
  }
}

TBL::Table::~Table() {
  std::ofstream ofs{Constant::DatabasesDirectory / this->_databaseName / (this->_tableName + Constant::FileExtension)};

  // Log Headers
  for (unsigned int i = 0; i < this->_headers.size(); ++i) {
    const Header& header = this->_headers[i];
    ofs << header.name << " " << SQL::TypeMapString.at(header.type) << Constant::FieldDelimiter << " ";
  }
  ofs << "\n";

  // Log Rows
  for (const auto& row : this->_rows) {
    for (unsigned int i = 0; i < row.size(); ++i) {
      switch (this->_headers[i].type)
      {
      case SQL::Type::Integer:
        ofs << std::get<int>(row[i]) << Constant::FieldDelimiter; 
        break;
      }
    }
    ofs << "\n";
  }
}

std::vector<TBL::Header> TBL::Table::readHeaders(std::istream& is, const std::string databaseName, const std::string tableName) 
// Create Vector of All Headers of a Line
{
  std::vector<Header> headers;

  std::string headerName, headerTypeStr;
  while (is >> headerName >> headerTypeStr) {
    Token::transformString(headerTypeStr, std::tolower);
    // Strip Trailing Comma if Present
    if (!headerTypeStr.empty() && headerTypeStr.back() == ',') headerTypeStr.pop_back();
  
    SQL::Type headerType;
    try {
      headerType = SQL::TypeMapEnum.at(headerTypeStr);
    } 
    catch (const std::out_of_range& e) {
      throw std::runtime_error("Unknown Type '" + headerTypeStr + "' For Header '" + headerName + 
                               "' In '" + databaseName + "." + tableName + "' Table\n");
    }
    headers.emplace_back(headerType, headerName);
  }

  return headers;
}

std::vector<TBL::fieldType> TBL::Table::createRow(std::istream& is) 
// Create Data From 1 Row
{
  std::vector<fieldType> row;
  std::vector<std::string> fields = Token::readValues(is);

  if (fields.size() != this->_headers.size()) throw std::runtime_error("Mismatched amount of value fields (" + std::to_string(fields.size()) + 
                                               ") and header fields (" + std::to_string(this->_headers.size()) +")");

  for (size_t i = 0; i < this->_headers.size(); ++i) {
    switch(this->_headers[i].type) {
      case SQL::Type::Integer:
        try {
          row.emplace_back(std::stoi(fields[i]));
        }
        catch (std::invalid_argument& e) {
          std::cerr << "Error in function " << e.what() << "\n";
          throw std::runtime_error("Error parsing '" + fields[i] + "' into an integer type");
        }
        catch (std::out_of_range& e) {
          std::cerr << "Error in function '" << e.what() << "'\n";
          throw std::runtime_error("Error truncating '" + fields[i] + "' into an integer type. Value too high/low");
        }
        break;
      default:
        throw std::runtime_error("Error parsing field #" + std::to_string(i + 1) +
                                 " in table " + this->_databaseName + "." + this->_tableName +
                                 ": unsupported type or invalid value '" + fields[i] + "'");
    }
  }

  return row;
}
