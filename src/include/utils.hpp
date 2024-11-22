#ifndef __UTILS_H
#define __UTILS_H
#include "parser.hpp"

inline void print_umap(std::unordered_map<std::string,Variables> &variables){
  for(const auto &x : variables){
    std::cout << x.first << " : ";
    Variables var = x.second;
    if (var.type == TokenType::LITERAL){
      std::cout <<   var.varName <<  " -> str " << std::endl;
    }else if (var.type == TokenType::INT){
      std::cout << var.intValue <<  " -> int " << std::endl;
    }else{
      std::cout << var.floatValue << " -> float " << std::endl;
    }
  }
}

inline void print_token(Lexer &lexer){
  Token token = lexer.getNextToken();
  while(token.type != TokenType::END){
    std::cout << token_to_str(token) << std::endl;
    token = lexer.getNextToken();
  }
}


#endif // !__UTILS_H
