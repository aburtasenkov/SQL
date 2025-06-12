#pragma once

#include <string>
#include <iostream>
#include <map>

enum class Operator : unsigned char {
  None, Create, Use
};

enum class Object : unsigned char {
  None, Table, Database
};

extern const std::map<std::string, Operator> OperatorMap;
extern const std::map<std::string, Object> ObjectMap;

std::string argumentsToString(int, char **); // Return One Lowercase Word from is

std::string toLower(std::string);
std::string getToken(std::istream&); // Convert Command Line Arguments Vector into Input Stream

template <typename T>
T getMapValue(std::istream&, const std::map<std::string, T>&);  // Return Value from a Map of a String-Key

std::istream& operator>>(std::istream&, Operator&); // Read Next Operator Token
std::istream& operator>>(std::istream&, Object&); // Read Next Object Token


std::string readUntilChar(std::istream&, char);