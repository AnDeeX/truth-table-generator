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
    if( arg.find( "-help" ) != string::npos )
      return helper();
    else if(  arg.find( "--reverse" ) != string::npos ||
              arg.find( "-r" ) != string::npos )
      return 1;
    else cout << "Argument " << arg << " unknown!" << endl;
  }
  return 0;
}

int Args::helper() const {
  system("cat src/pages/help.txt | less");
  return 0;
}