#pragma once

#include <map>
#include <string>
#include <iostream>

namespace SQL {
  enum class Operator : unsigned char {
    None, Create, Use
  };
  
  enum class Object : unsigned char {
    None, Table, Database
  };
  
  enum class Type : unsigned char {
    Integer
  };
  
  extern const std::map<std::string, Operator> OperatorMap;
  extern const std::map<std::string, Object> ObjectMap;
  
  extern const std::map<std::string, Type> TypeMapEnum;
  extern const std::map<Type, std::string> TypeMapString;
  
  template <typename T>
  T getMapValue(std::istream&, const std::map<std::string, T>&);  // Return Value from a Map of a String-Key

}