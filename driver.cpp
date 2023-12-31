#include <cstring>
#include <cstddef>
#include <istream>
#include <iostream>
#include <fstream>
#include <vector>

#include "scanner.hh"
#include "parser.tab.hh"

int main(const int argc, const char **argv)
{

  using namespace std;
  fstream in_file;

  in_file.open(argv[1], ios::in);
  // Generate a scanner
  IPL::Scanner scanner(in_file);
  // Generate a Parser, passing the scanner as an argument.
  // Remember %parse-param { Scanner  &scanner  }
  IPL::Parser parser(scanner);
  
  #ifdef YYDEBUG
   parser.set_debug_level(1);
  #endif 

  parser.parse();
}


