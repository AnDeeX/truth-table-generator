#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>
#include <vector>

using namespace std;

class Args
{
  public:
    Args   ( int argv, char * argc[] );
    ~Args  ( void );

    int processArguments( void );
  protected:
  private:

    int helper( void ) const ;

    vector<string> m_argv;
};

#endif