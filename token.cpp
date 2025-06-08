#include "token.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

std::string argumentsToString(int argc, char ** argv) 
// Convert Command Line Arguments Vector into Input Stream 
{
  std::ostringstream stream;
  for (int i = 1; i < argc; ++i) {
    stream << argv[i] << " ";
  }
  return stream.str();
}

std::string getToken(std::istream& is) 
// Return One Lowercase Word from is
{
  std::string token;
  is >> token;
  std::transform(token.begin(), token.end(), token.begin(), 
    [](unsigned char ch){
      return std::tolower(ch);          
    }
  );
  return token;
}