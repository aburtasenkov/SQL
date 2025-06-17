#include "token.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

#include "SQL.hpp"

std::string Token::argumentsToString(int argc, char ** argv) 
// Convert Command Line Arguments Vector into Input Stream 
{
  std::ostringstream stream;
  for (int i = 1; i < argc; ++i) {
    stream << argv[i] << " ";
  }
  return stream.str();
}

void Token::transformString(std::string& str, int (*func)(int))
// Transform str, Applying func to Each Character
{
  std::transform(str.begin(), str.end(), str.begin(), 
  [func](unsigned char ch){
    return func(ch);          
  });
}

std::string Token::getToken(std::istream& is) 
// Return One Lowercase Word from is
{
  std::string token;
  is >> token;
  Token::transformString(token, static_cast<int(*)(int)>(std::tolower));
  return token;
}

std::string Token::getToken(std::istream& is, char delim) 
// Return One Lowercase Word from is
// Read Only Until delim
{
  std::string token = Token::readUntilChar(is, delim);
  Token::transformString(token, static_cast<int(*)(int)>(std::tolower));
  return token;
}

std::istream& Token::operator>>(std::istream& is, SQL::Operator& op)
// Read Next Operator Token
{
  op = SQL::getMapValue(is, SQL::OperatorMap);
  return is;
}

std::istream& Token::operator>>(std::istream& is, SQL::Object& obj) 
// Read Next Object Token
{
  obj = SQL::getMapValue(is, SQL::ObjectMap);
  return is;
}

std::string Token::readUntilChar(std::istream& is, char delimiter) {
  std::string str;
  std::getline(is, str, delimiter);
  return str;
}