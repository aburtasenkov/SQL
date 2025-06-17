#include <iostream>
#include <exception>

#include "source/token.hpp"
#include "logic.hpp"

int main(int argc, char ** argv) {
  std::istringstream is {Token::argumentsToString(argc, argv)};
  SQL::Operator op;
  while (Token::operator>>(is, op)) {
    try {
      switch (op) {
        case SQL::Operator::None:
          std::cerr << "main::BadSyntaxError\n";
          break;
        case SQL::Operator::Create:
          create(is);
          break;
        case SQL::Operator::Use:
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