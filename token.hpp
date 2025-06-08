#pragma once

#include <string>
#include <iostream>

std::string argumentsToString(int argc, char ** argv); // Return One Lowercase Word from is
std::string getToken(std::istream& is); // Convert Command Line Arguments Vector into Input Stream