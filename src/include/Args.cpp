#include <iostream>
#include <string>
#include <vector>

#include "Args.hpp"
#include "Generator.hpp"

using namespace std;


Args::Args( int argc, char * argv[] ) : m_argv(argv + 1, argv + argc){}

Args::~Args(){}


int Args::processArguments(){
  for( auto arg : m_argv ){
    if( arg.find( "help" ) != string::npos )
      return helper();
  }
  return 0;
}

int Args::helper() const {
  system("cat src/pages/help.txt | less");
  return 1;
}