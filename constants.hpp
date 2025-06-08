#pragma once

#include <filesystem>
#include <string>

extern const std::filesystem::path DatabasesDirectory;  // File Directory
extern const std::string FileExtension; // Self Explanatory

// Characters for Parsing the Tables
extern const char FieldDelimiter; // Delimiter For a Field in .csv Table of a Database
// Delimiters for Type of a Field 
extern const char TypeOpener;
extern const char TypeCloser;