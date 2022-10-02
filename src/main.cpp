#include <iostream>
#include <string>

#include "include/Args.hpp"
#include "include/Generator.hpp"

using namespace std;

int main( int argc, char * argv[] ){
  Args args = Args(argc, argv);
  if( args.processArguments() ) return 1;

  while( true ){
    Generator generator = Generator();
    if( ! generator.getFormula() ) break;
    generator.generate();
  }

  return 0;
}