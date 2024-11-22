#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <cctype>
#include <iostream>

// Token types
enum class TokenType {
  FLOAT,INT, IDENTIFIER, ASSIGN, PRINT, NUMBER, 
  PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, 
  NEWLINE, END, COMMENT,STRING,LITERAL
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

    if (current == '#'){
      size_t start = pos;
      while(input[pos] != '\n')pos++;
      return {TokenType::COMMENT,input.substr(start,pos-start)};
    }
    if (current == '\n') {
      pos++;
      return { TokenType::NEWLINE, "\\n" };
    }

    if (current == '"'){
      size_t start = ++pos;
      while(isalpha(input[pos]) || input[pos] != '"') pos++;
      std::string i = input.substr(start,pos - start);
      return {TokenType::LITERAL,input.substr(start,(pos++)-start)};
    }

    if (isdigit(current)) {
      size_t start = pos;
      while (pos < input.size() && isdigit(input[pos])) pos++;
      while (input[pos] == '.' || isdigit(input[pos])) pos++;
      return { TokenType::NUMBER, input.substr(start, pos - start) };
    }

    if (isalpha(current)) {
      size_t start = pos;
      while (pos < input.size() && isalnum(input[pos])) pos++;
      std::string word = input.substr(start, pos - start);
      if (word == "str") return { TokenType::STRING, word };
      if (word == "int") return { TokenType::INT, word };
      if (word == "float") return { TokenType::FLOAT, word };
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

  // FLOAT,INT, IDENTIFIER, ASSIGN, PRINT, NUMBER, 
  // PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, 
  // NEWLINE, END, COMMENT

inline std::string token_to_str(const Token &token){
  std::string value = token.value;
  std::string buff = "Value : "+value + "\n";
  switch (token.type) {
    case TokenType::FLOAT : return buff + "Token : " + "FLOAT" + "\n";
    case TokenType::INT : return buff + "Token : " + "INT" + "\n";
    case TokenType::IDENTIFIER : return buff + "Token : " + "IDENTIFIER" + "\n";
    case TokenType::ASSIGN : return buff + "Token : " + "ASSIGN" + "\n";
    case TokenType::PRINT : return buff + "Token : " + "PRINT" + "\n";
    case TokenType::NUMBER : return buff + "Token : " + "NUMBER" + "\n";
    case TokenType::PLUS : return buff + "Token : " + "PLUS" + "\n";
    case TokenType::MINUS : return buff + "Token : " + "MINUS" + "\n";
    case TokenType::MULTIPLY : return buff + "Token : " + "MULTIPLY" + "\n";
    case TokenType::DIVIDE : return buff + "Token : " + "DIVIDE" + "\n";
    case TokenType::LPAREN : return buff + "Token : " + "LPAREN" + "\n";
    case TokenType::RPAREN : return buff + "Token : " + "RPAREN" + "\n";
    case TokenType::NEWLINE : return buff + "Token : " + "NEWLINE" + "\n";
    case TokenType::END : return buff + "Token : " + "END" + "\n";
    case TokenType::COMMENT : return buff + "Token : " + "COMMENT" + "\n";
    case TokenType::STRING : return buff + "Token : " + "STRING" + "\n";
    case TokenType::LITERAL : return buff + "Token : " + "LITERAL" + "\n";
    default : return buff + "Token : UNKNOWN TOKEN";
  }
}

#endif
