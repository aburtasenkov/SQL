#include "token.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

const std::map<std::string, Operator> OperatorMap {
  {"create", Operator::Create},
  {"use", Operator::Use}
};

const std::map<std::string, Object> ObjectMap {
  {"table", Object::Table}, 
  {"database", Object::Database}
};

const std::map<std::string, Type> TypeMapEnum{
  {"integer", Type::Integer}
};

const std::map<Type, std::string> TypeMapString {
  {Type::Integer, "integer"}
};

std::string argumentsToString(int argc, char ** argv) 
// Convert Command Line Arguments Vector into Input Stream 
{
  std::ostringstream stream;
  for (int i = 1; i < argc; ++i) {
    stream << argv[i] << " ";
  }
  return stream.str();
}

void transformString(std::string& str, int (*func)(int))
// Transform str, Applying func to Each Character
{
  std::transform(str.begin(), str.end(), str.begin(), 
  [func](unsigned char ch){
    return func(ch);          
  });
}

std::string getToken(std::istream& is) 
// Return One Lowercase Word from is
{
  std::string token;
  is >> token;
  transformString(token, std::tolower);
  return token;
}

std::string getToken(std::istream& is, char delim) 
// Return One Lowercase Word from is
// Read Only Until delim
{
  std::string token = readUntilChar(is, delim);
  transformString(token, std::tolower);
  return token;
}

template <typename T>
T getMapValue(std::istream& is, const std::map<std::string, T>& map) 
// Return Value from a Map of a String-Key
{
  std::string token = getToken(is);
  try {
    return map.at(token);
  }
  catch (const std::out_of_range& e) {
    return T::None;
  }
}

std::istream& operator>>(std::istream& is, Operator& op)
// Read Next Operator Token
{
  op = getMapValue(is, OperatorMap);
  return is;
}

std::istream& operator>>(std::istream& is, Object& obj) 
// Read Next Object Token
{
  obj = getMapValue(is, ObjectMap);
  return is;
}

std::string readUntilChar(std::istream& is, char delimiter) {
  std::string str;
  std::getline(is, str, delimiter);
  return str;
}