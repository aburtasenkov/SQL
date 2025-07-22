#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "SQL.hpp"

namespace Token{  
  std::string argumentsToString(int, char **); // Convert Command Line Arguments Vector into Input Stream 
  
  void transformString(std::string&, int (*)(int)); // Transform str, Applying func to Each Character
  
  // Return One Lowercase Word from is ...
  std::string getToken(std::istream&);  // Until Whitespace
  std::string getToken(std::istream& is, char delim); // Until delim
  std::istream& operator>>(std::istream&, SQL::Operator&); // Read Next Operator Token
  std::istream& operator>>(std::istream&, SQL::Object&); // Read Next Object Token
  std::istream& operator>>(std::istream&, SQL::Keyword&); // Read Next Keyword Token
  
  
  std::string readUntilChar(std::istream&, char);
  std::vector<std::string> readValues(std::istringstream& is); // Read Values That Need To Be Inserted Somewhere
                                                        // Syntax: Value1, Value2, Value3, ...
};