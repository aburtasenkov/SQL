#include "constants.hpp"

#include <filesystem>
#include <string>

const std::filesystem::path DatabasesDirectory = "databases";
const std::string FileExtension = ".csv";
const char FieldDelimiter = ',';
const char TypeOpener = '(';
const char TypeCloser = ')';