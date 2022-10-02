#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <string>

#define IS_NUM( x ) ( (x >= '0' && x <= '1') ? true : false )
#define IS_ATOM( x )( (x >= 'a' && x <= 'z') ? true : false )
#define NEGATE_CHAR( x ) ( x == '0' ? '1' : '0' )
#define NUM( x ) ( ( x ) - 48 )
#define CHAR( x ) ( ( x ) + 48 )
#define CONJUCTION '&'
#define DISJUNCTION '|'
#define NEGATION '-'
#define IMPLICATION '>'
#define EQUIVALENCE '='
#define XOR '^'
#define TAUTOLOGY 'T'
#define CONTRADICTION 'K'
#define OPENING_BRACKET '('
#define CLOSING_BRACKET ')'

using namespace std;

class Generator
{
  public:
    Generator   ( void );
    ~Generator  ( void );

    bool getFormula();
    void generate();
  protected:
  private:
    bool processFormula( string );
    void processConstants( void );
    bool containsIllegalCharacters( string );
    bool isValid( string );
    bool findAtoms( void );

    int calculateRow( void );

    bool findOperands( int, string, pair<char, int> &, pair<char, int> & ) const ;
    bool findNegator ( int, string, pair<char, int> & ) const ;
    bool dissolveBrackets( int, string, char &, int & ) const ;

    char conjunction  ( char, char ) const ;
    char disjunction  ( char, char ) const ;
    char implication  ( char, char ) const ;
    char equivalence  ( char, char ) const ;
    char myXor          ( char, char ) const ;

    void printVSeparator( char ) const ;
    void printHSeparator( void ) const ;
    void printAtoms     ( void ) const ;
    

    string m_formula;
    vector<pair<char, bool>> m_atoms;

    const vector< char > m_binaryOperators = { 
      CONJUCTION, 
      DISJUNCTION, 
      IMPLICATION, 
      EQUIVALENCE, 
      XOR };
    const vector<char> m_allowedSymbols = { 
    CONJUCTION, 
    DISJUNCTION, 
    NEGATION, 
    IMPLICATION , 
    EQUIVALENCE, 
    TAUTOLOGY, 
    CONTRADICTION, 
    XOR, 
    OPENING_BRACKET, CLOSING_BRACKET , ' ', '\n' };
};

#endif