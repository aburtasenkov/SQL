#pragma once

#include <filesystem>
#include <iostream>

#include "source/database.hpp"

extern DB::Database currentDatabase;

// SQL Commands
void create(std::istream&); // Create Operation 
void createTable(std::istream&); // Create Table 

DB::Database createDatabase(std::istream&); // Create New Database
void useDatabase(std::istream&); // Change Current Database in Use