#pragma once

#include <string>
#include <iostream>

#include "SQL.hpp"

namespace Token{  
  std::string argumentsToString(int, char **); // Convert Command Line Arguments Vector into Input Stream 
  
  void transformString(std::string&, int (*)(int)); // Transform str, Applying func to Each Character
  
  // Return One Lowercase Word from is ...
  std::string getToken(std::istream&);  // Until Whitespace
  std::string getToken(std::istream& is, char delim); // Until delim
  std::istream& operator>>(std::istream&, SQL::Operator&); // Read Next Operator Token
  std::istream& operator>>(std::istream&, SQL::Object&); // Read Next Object Token
  
  
  std::string readUntilChar(std::istream&, char);
};