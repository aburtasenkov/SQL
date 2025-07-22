#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <variant>

#include "token.hpp"
#include "SQL.hpp"

namespace TBL {
  struct Header{
    SQL::Type type;
    std::string name;

    Header(const SQL::Type& t, const std::string& n)
    :type(t), name(n) {}
  };
  
  using fieldType = std::variant<int>;
  
  // CURRENTLY ONLY INTEGER SUPPORT
  class Table {
    public:
    Table(std::string, std::string, std::vector<Header>); // Initializer for Creating New Tables
    Table(std::string, std::string);  // Initializer for Existing Tables
    ~Table();
    static std::vector<Header> readHeaders(std::istream&, const std::string, const std::string);
    const std::vector<Header>& getHeaders() { return _headers; }
    void insert(const std::vector<fieldType>& v) { _rows.push_back(v); }
    std::vector<fieldType> createRow(std::istream&);

    private:
    std::string _databaseName;
    std::string _tableName;
    std::vector<Header> _headers;
    std::vector<std::vector<fieldType>> _rows;
    
  };
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