#pragma once

#include <filesystem>
#include <string>

namespace Constant{
  extern const std::filesystem::path DatabasesDirectory;  // File Directory
  extern const std::string FileExtension; // Self Explanatory
  
  // Characters for Parsing the Tables
  extern const char FieldDelimiter; // Delimiter For a Field in .csv Table of a Database
  // Delimiters for Parameters in SQL Syntax 
  extern const char ParameterOpener;
  extern const char ParameterCloser;
};