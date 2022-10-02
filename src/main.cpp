#include <iostream>
#include <string>

#include "include/Args.hpp"
#include "include/Generator.hpp"

using namespace std;

int main( int argc, char * argv[] ){
  Args args = Args(argc, argv);
  int rev = args.processArguments(); 

  while( true ){
    Generator generator = Generator();
    if( ! generator.getFormula() ) break;
    generator.generate( rev );
  }

  return 1;
}