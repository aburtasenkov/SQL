#include "SQL.hpp"

#include <map>
#include <string>
#include <iostream>

#include "token.hpp"

const std::map<std::string, SQL::Operator> SQL::OperatorMap {
  {"create", SQL::Operator::Create},
  {"use", SQL::Operator::Use},
  {"insert", SQL::Operator::Insert},
};

const std::map<std::string, SQL::Object> SQL::ObjectMap {
  {"table", SQL::Object::Table}, 
  {"database", SQL::Object::Database},
};

const std::map<std::string, SQL::Keyword> SQL::KeywordMap {
  {"into", SQL::Keyword::Into},
  {"values", SQL::Keyword::Values},
};

const std::map<std::string, SQL::Type> SQL::TypeMapEnum{
  {"integer", SQL::Type::Integer}
};

const std::map<SQL::Type, std::string> SQL::TypeMapString {
  {SQL::Type::Integer, "integer"}
};

template <typename T>
T SQL::getMapValue(std::istream& is, const std::map<std::string, T>& map) 
// Return Value from a Map of a String-Key
{
  std::string token = Token::getToken(is);
  try {
    return map.at(token);
  }
  catch (const std::out_of_range& e) {
    return T::None;
  }
}

// Explicit instantiations for Required Types
namespace SQL {
  template SQL::Operator SQL::getMapValue<SQL::Operator>(std::istream& is, const std::map<std::string, SQL::Operator>& map);
  template SQL::Object SQL::getMapValue<SQL::Object>(std::istream& is, const std::map<std::string, SQL::Object>& map);
  template SQL::Keyword SQL::getMapValue<SQL::Keyword>(std::istream& is, const std::map<std::string, SQL::Keyword>& map);
}