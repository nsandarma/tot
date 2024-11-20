#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <cctype>
#include <iostream>

// Token types
enum class TokenType {
  INT, IDENTIFIER, ASSIGN, PRINT, NUMBER, 
  PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, 
  NEWLINE, END
};

struct Token {
  TokenType type;
  std::string value;
};

// Lexer: Tokenize input
class Lexer {
  std::string input;
  size_t pos;
  public:
  Lexer(const std::string& src) : input(src), pos(0) {}

  Token getNextToken() {
    while (pos < input.size() && isspace(input[pos]) && input[pos] != '\n') pos++;

    if (pos >= input.size()) return { TokenType::END, "" };

    char current = input[pos];
    if (current == '\n') {
      pos++;
      return { TokenType::NEWLINE, "\\n" };
    }

    if (isdigit(current)) {
      size_t start = pos;
      while (pos < input.size() && isdigit(input[pos])) pos++;
      return { TokenType::NUMBER, input.substr(start, pos - start) };
    }

    if (isalpha(current)) {
      size_t start = pos;
      while (pos < input.size() && isalnum(input[pos])) pos++;
      std::string word = input.substr(start, pos - start);
      if (word == "int") return { TokenType::INT, word };
      if (word == "print") return { TokenType::PRINT, word };
      return { TokenType::IDENTIFIER, word };
    }

    switch (current) {
      case '=': pos++; return { TokenType::ASSIGN, "=" };
      case '+': pos++; return { TokenType::PLUS, "+" };
      case '-': pos++; return { TokenType::MINUS, "-" };
      case '*': pos++; return { TokenType::MULTIPLY, "*" };
      case '/': pos++; return { TokenType::DIVIDE, "/" };
      case '(': pos++; return { TokenType::LPAREN, "(" };
      case ')': pos++; return { TokenType::RPAREN, ")" };
      default: throw std::runtime_error("Unexpected character: " + std::string(1, current));
    }
  }
};

#endif
