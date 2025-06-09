#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <variant>

enum class Type : unsigned char {
  Integer
};

extern const std::map<std::string, Type> TypeMapEnum;
extern const std::map<Type, std::string> TypeMapString;

struct Header{
  Type type;
  std::string name;
};

using fieldType = std::variant<int>;

// CURRENTLY ONLY INTEGER SUPPORT
class Table {
  public:
  Table(std::string, std::string);
  ~Table();
  private:
  std::string _databaseName;
  std::string _tableName;
  std::vector<Header> _headers;
  std::vector<std::vector<fieldType>> _rows;
  
  Header _getHeader(std::istream&);
  std::vector<Header> _readHeaders(std::istream&);

  std::vector<fieldType> _getRow(std::istream&);
};

// Example
/*
Primary Key, Age, Money
1             10  1000
2             18  12345
3             65  999.999.999

Steps:
  1. Read Headers
    1.0 Read Header Line
    1.1 Read Field Name
    1.2 Read Header Type in "(...)"
    1.3 Create Vector of structs(Type, Name)
  2. Read Fields line by line
    2.1 Read Line
    2.2 Create Vector of structs that contain the Field Value as void*
    2.3 Pushback vector to 

Notes:
2d Vector for data
*/