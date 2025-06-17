#pragma once

#include <filesystem>
#include <iostream>

#include "database.hpp"

extern Database currentDatabase;

// SQL Commands
void create(std::istream&); // Create Operation 
void createTable(std::istream&); // Create Table 

Database createDatabase(std::istream&); // Create New Database
void useDatabase(std::istream&); // Change Current Database in Use