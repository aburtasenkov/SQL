#pragma once

#include <filesystem>
#include <iostream>

#include "database.hpp"

extern Database currentDatabase;

void create(std::istream&); // SQL Create Operation 

Database createDatabase(std::istream&); // Create New Database
void useDatabase(std::istream&); // Change Current Database in Use