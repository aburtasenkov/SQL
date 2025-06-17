#include "constants.hpp"

#include <filesystem>
#include <string>

const std::filesystem::path Constant::DatabasesDirectory = "databases";
const std::string Constant::FileExtension = ".csv";
const char Constant::FieldDelimiter = ',';
const char Constant::ParameterOpener = '(';
const char Constant::ParameterCloser = ')';