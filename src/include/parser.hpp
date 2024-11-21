#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.hpp"
#include <unordered_map>

class Parser {
  Lexer lexer;
  Token currentToken;

  void eat(TokenType type) {
    if (currentToken.type == type)
      currentToken = lexer.getNextToken();
    else
      throw std::runtime_error("Unexpected token: " + currentToken.value);
  }

  int parseFactor() {
    if (currentToken.type == TokenType::NUMBER) {
      int value = stoi(currentToken.value);
      eat(TokenType::NUMBER);
      return value;
    } else if (currentToken.type == TokenType::LPAREN) {
      eat(TokenType::LPAREN);
      int result = parseExpression();
      eat(TokenType::RPAREN);
      return result;
    } else {
      if(variables.count(currentToken.value)){
        int value = variables.at(currentToken.value);
        eat(TokenType::IDENTIFIER);
        return value;
      }
      throw std::runtime_error("Unexpected token in factor: " + currentToken.value);
    }
  }

  int parseTerm() {
    int result = parseFactor();
    while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
      if (currentToken.type == TokenType::MULTIPLY) {
        eat(TokenType::MULTIPLY);
        result *= parseFactor();
      } else if (currentToken.type == TokenType::DIVIDE) {
        eat(TokenType::DIVIDE);
        result /= parseFactor();
      }
    }
    return result;
  }

  int parseExpression() {
    int result = parseTerm();
    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
      if (currentToken.type == TokenType::PLUS) {
          eat(TokenType::PLUS);
          result += parseTerm();
      } else if (currentToken.type == TokenType::MINUS) {
          eat(TokenType::MINUS);
          result -= parseTerm();
      }
    }
    return result;
  }

  public:
  std::unordered_map<std::string, int> variables;
  Parser(Lexer lex) : lexer(lex), currentToken(lexer.getNextToken()) {}

  void parseProgram() {
    while (currentToken.type != TokenType::END) {
      if (currentToken.type == TokenType::INT) {
        eat(TokenType::INT);
        std::string varName = currentToken.value;
        eat(TokenType::IDENTIFIER);
        eat(TokenType::ASSIGN);
        int value = parseExpression();
        variables[varName] = value;
      } else if (currentToken.type == TokenType::PRINT) {
        eat(TokenType::PRINT);
        eat(TokenType::LPAREN);
        std::string varName = currentToken.value;
        eat(TokenType::IDENTIFIER);
        eat(TokenType::RPAREN);

        if (variables.find(varName) != variables.end()) {
          std::cout << variables[varName] << std::endl;
        } else {
          throw std::runtime_error("Variable not found: " + varName);
        }
      }
      if (currentToken.type == TokenType::NEWLINE)
        eat(TokenType::NEWLINE);
    }
  }
};

#endif
