#include "token.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

std::string argumentsToString(int argc, char ** argv) 
// convert command line arguments vector into input stream 
{
  std::ostringstream stream;
  for (int i = 1; i < argc; ++i) {
    stream << argv[i] << " ";
  }
  return stream.str();
}

std::string getToken(std::istream& is) 
// return one lowercase word from is
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