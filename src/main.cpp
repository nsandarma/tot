#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/utils.hpp"
#include <fstream>


void read_file(const std::string filename, std::string &buff){
  std::ifstream f(filename);
  std::string line;
  while(getline(f,line)){
    buff.append(line+'\n');
  }
  f.close();
}

int main(int argc, char* argv[]){
  if (argc < 2){
    std::cerr << "no source file !";
    exit(1);
  }

  std::string code;
  read_file(argv[1],code);

  Lexer lexer(code);
  Parser parser(lexer);
  try {
    parser.parseProgram();
  } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
