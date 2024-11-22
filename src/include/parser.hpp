#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.hpp"
#include <unordered_map>

struct Variables{
  std::string varName;
  TokenType type;
  union{
    int intValue;
    float floatValue;
  };
};

class Parser {
  Lexer lexer;
  Token currentToken;

  template<typename type>
  type get_value_var(std::string &varName){
    Variables var = variables[varName];
    if(var.type == TokenType::INT){
      return var.intValue;
    }
    else{
      return var.floatValue;
    }
  }

  void eat(TokenType type) {
    if (currentToken.type == type)
      currentToken = lexer.getNextToken();
    else
      throw std::runtime_error("Unexpected token: " + currentToken.value);
  }

  float parseFactor() {
    if (currentToken.type == TokenType::NUMBER) {
      float value = stof(currentToken.value);
      eat(TokenType::NUMBER);
      return value;
    } else if (currentToken.type == TokenType::LPAREN) {
      eat(TokenType::LPAREN);
      float result = parseExpression();
      eat(TokenType::RPAREN);
      return result;
    } else {
      if (variables.count(currentToken.value)) {
        if (variables[currentToken.value].type == TokenType::INT) {
          int value = get_value_var<int>(currentToken.value);
          eat(TokenType::IDENTIFIER);
          return static_cast<float>(value);
        } else {
          float value = get_value_var<float>(currentToken.value);
          eat(TokenType::IDENTIFIER);
          return value;
        }
      }
      throw std::runtime_error("Unexpected token in factor: " + currentToken.value); }
}

  float parseTerm() {
    float result = parseFactor();
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

  float parseExpression() {
    float result = parseTerm();
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
  std::unordered_map<std::string, Variables> variables;
  Parser(Lexer lex) : lexer(lex), currentToken(lexer.getNextToken()) {}

  void parseProgram() {
    while (currentToken.type != TokenType::END) {
      if (currentToken.type == TokenType::COMMENT){
        eat(currentToken.type);
      }
      if (currentToken.type == TokenType::INT || currentToken.type == TokenType::FLOAT) {
        TokenType varType = currentToken.type;
        eat(currentToken.type);
        std::string varName = currentToken.value;
        eat(TokenType::IDENTIFIER);
        eat(TokenType::ASSIGN);
        float value = parseExpression();
        Variables val;
        val.varName = varName;
        if (varType == TokenType::INT){
          val.type = TokenType::INT;
          val.intValue = static_cast<int>(value);
        }else{
          val.type = TokenType::FLOAT;
          val.floatValue = value;
        }
        variables[varName] = val;
      } else if (currentToken.type == TokenType::PRINT) {
        eat(TokenType::PRINT);
        eat(TokenType::LPAREN);
        std::string varName = currentToken.value;
        eat(TokenType::IDENTIFIER);
        eat(TokenType::RPAREN);

        if (variables.find(varName) != variables.end()) {
          if(variables[varName].type == TokenType::INT){
            std::cout << variables[varName].intValue << std::endl;
          }else{
            std::cout << variables[varName].floatValue << std::endl;
          }

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
