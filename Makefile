CXX = g++-9
EXE = iplC
CXXDEBUG = -g -Wall
CXXSTD = -std=c++11


.PHONY: all

all: parser lexer symbol_table_generator
	$(CXX) $(CXXSTD) $(CXXDEBUG) -o iplC driver.cpp parser.o scanner.o symbol_table.o

parser: parser.yy scanner.hh
	bison -d -v $<
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c parser.tab.cc -o parser.o

# type_generator: type.hh symbtab.hh
# 	$(CXX) $(CXXSTD) $(CXXDEBUG) -c type.cpp -o type.o

symbol_table_generator: symbol_table.hh
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c symbol_table.cpp -o symbol_table.o

# ast_generator: ast.hh type.hh
# 	$(CXX) $(CXXSTD) $(CXXDEBUG) -c ast.cpp -o ast.o

lexer: scanner.l scanner.hh parser.tab.hh parser.tab.cc
	flex++ --outfile=scanner.yy.cc $<
		$(CXX) $(CXXSTD) $(CXXDEBUG) -c scanner.yy.cc -o scanner.o

clean:
	rm parser.o scanner.o symbol_table.o iplC parser.tab.hh parser.tab.cc scanner.yy.cc stack.hh parser.output location.hh position.hh 
