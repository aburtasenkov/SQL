#include <iostream>
#include <exception>

#include "token.hpp"
#include "logic.hpp"

int main(int argc, char ** argv) {
  std::istringstream is {argumentsToString(argc, argv)};
  Operator op;
  while (is >> op) {
    try {
      switch (op) {
        case Operator::None:
          std::cerr << "main::BadSyntaxError\n";
          break;
        case Operator::Create:
          create(is);
          break;
        case Operator::Use:
          useDatabase(is);
          break;
      }
    }
    catch (const std::runtime_error& e) {
      std::cerr << e.what() << "\n";
      exit(1);
    }
  }
  return 0;
}