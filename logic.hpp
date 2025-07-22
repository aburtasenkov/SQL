#pragma once

#include <filesystem>
#include <iostream>

#include "source/database.hpp"

extern DB::Database currentDatabase;

// SQL Commands
void create(std::istream&); // Create Operation 
TBL::Table createTable(std::istream&); // Create Table 

void insert(std::istream&); // SQL Insert Command
void insertInto(std::istream&);

DB::Database createDatabase(std::istream&); // Create New Database
void useDatabase(std::istream&); // Change Current Database in Use