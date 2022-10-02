#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "Generator.hpp"

Generator::Generator   ( void ){};
Generator::~Generator  ( void ){};

bool Generator::getFormula(){
  string rawInput;
  getline( cin, rawInput);
  return processFormula( rawInput );
}

void Generator::generate(){
  printVSeparator('=');
  printAtoms();
  printHSeparator();
  cout << m_formula << endl;
  printVSeparator('-');

  int currentCase = pow( 2, m_atoms.size()) - 1; 

  while( currentCase >= 0 ){
    for( int atom = 0; atom < m_atoms.size(); atom++ )
      m_atoms[ m_atoms.size() - atom -1 ].second = ( ( currentCase >> atom ) & 1 );

    for( auto atom : m_atoms )
      cout << atom.second << " ";

    printHSeparator();
    cout << calculateRow() << endl;
    currentCase--;
  }
  printVSeparator('=');
}

char Generator::conjunction( char p, char q ) const {
  return ( p & q );
}
char Generator::disjunction( char p, char q ) const {
  return ( p | q );
}
char Generator::implication( char p, char q ) const {
  return CHAR( ( ! NUM( p ) ) | NUM( q ) );
}
char Generator::equivalence( char p, char q ) const {
  return conjunction( implication(p, q), implication(q, p) );
}
char Generator::myXor( char p, char q ) const {
  return CHAR( p != q );
}

int Generator::calculateRow(){

  string copy = m_formula;

  for( auto atom : m_atoms )
    replace( copy.begin(), copy.end(), atom.first, atom.second ? '1' : '0' );

  int pos = 0;
  while( pos < copy.length() ){
    if( find( m_binaryOperators.begin(), m_binaryOperators.end(), copy[ pos ] ) != m_binaryOperators.end() ){
      pair<char, int> lhs = { 0, -1 };
      pair<char, int> rhs = { 0, -1 };
      if( findOperands( pos, copy, lhs, rhs ) ){
        switch( copy[ pos ] ){
          case CONJUCTION:
            copy.erase( copy.begin() + lhs.second, copy.begin() + rhs.second + 1 );
            copy.insert( lhs.second, 1, conjunction( lhs.first, rhs.first ));
          break;
          case DISJUNCTION:
            copy.erase( copy.begin() + lhs.second, copy.begin() + rhs.second + 1);
            copy.insert( lhs.second, 1, disjunction( lhs.first, rhs.first ));
          break;
          case IMPLICATION:
            copy.erase( copy.begin() + lhs.second, copy.begin() + rhs.second + 1);
            copy.insert( lhs.second, 1, implication( lhs.first, rhs.first ));
          break;
          case EQUIVALENCE:
            copy.erase( copy.begin() + lhs.second, copy.begin() + rhs.second + 1);
            copy.insert( lhs.second, 1, equivalence( lhs.first, rhs.first ));
          break;
          case XOR:
            copy.erase( copy.begin() + lhs.second, copy.begin() + rhs.second + 1);
            copy.insert( lhs.second, 1, myXor( lhs.first, rhs.first ));
          break;
        }
        pos = 0;
      }
    }else if( copy[ pos ] == NEGATION ){
      pair<char, int> negator = { 0, -1 };
      if( findNegator( pos, copy, negator ) ){
        copy.erase( copy.begin() + pos, copy.begin() + negator.second + 1);
        copy.insert( pos, 1, negator.first );
        pos = 0;
      }
    }else if( copy[ pos ] == OPENING_BRACKET ){
      char atom = 0;
      int bracketPair = -1;
      if( dissolveBrackets( pos, copy, atom, bracketPair ) ){
        copy.erase( copy.begin() + pos, copy.begin() + bracketPair + 1 );
        copy.insert( pos, 1, atom );
        pos = 0;
      }
    }
    pos++;
  }
  for(auto character : copy){
    if( character == '0' || character == '1' )
      return character - 48;
  }
  return -1;
}

bool Generator::dissolveBrackets( int position, string formula, char & atom, int & bracketPair ) const {
  do{
    position++;
    if( IS_NUM( formula[ position ] ) ){
      if( atom == 0 )
        atom = formula[ position ];
      else return false;
    }else if( formula[ position ] == CLOSING_BRACKET ){
      bracketPair = position;
      return true;
    }else if( formula[ position ] != ' ' ){
      break;
    }
  }while( position < formula.length() );
  return false;
}

bool Generator::findNegator( int position, string formula, pair<char, int> & negator ) const {
  do{
    position++;
    if( formula[ position ] == '0' | formula[ position ] == '1' | formula[ position ] == '-' ){
      if( formula[ position ] != '-' )
        negator = { NEGATE_CHAR( formula[ position ] ), position };
      else
        negator = { ' ', position };
      return true;
    }else if( formula[ position ] != ' ' ){
      break;
    }
  }while( position < formula.length() -1 );
  return false;
}

bool Generator::findOperands( int operandPosition, string formula, pair<char, int> & lhs, pair<char, int> & rhs ) const {
  int position = operandPosition;
  int increment = -1;
  while( position > 0 && position < formula.length() - 1 ){
    position += increment;
    if( formula[ position ] == '0' || formula[ position ] == '1' ){
      if( lhs.second == -1 ){
        lhs.first = formula[ position ];
        lhs.second = position;
        increment = 1;
        position = operandPosition;
      }else{
        rhs.first = formula[ position ];
        rhs.second = position;
        return true;
      }
    }else if( formula[ position ] != ' ' ){
      break;
    }
  }
  return false;
} 

bool Generator::processFormula( string input ){
  if( containsIllegalCharacters( input ) ) return false;
  m_formula = input;
  if( ! findAtoms() ) return false;
  if( isValid( input ) ) return false;
  processConstants();
  return true;
}

void Generator::processConstants(){
  replace( m_formula.begin(), m_formula.end(), CONTRADICTION, '0' );
  replace( m_formula.begin(), m_formula.end(), TAUTOLOGY    , '1' );
}

bool Generator::containsIllegalCharacters( string input ){
  for( int character = 0; character < input.length() ; character++ ){
    if( find( m_allowedSymbols.begin(), m_allowedSymbols.end(), input[ character ] ) == m_allowedSymbols.end() ){
      if( input[ character ] < 'a' | input[ character ] > 'z' ){
        for( int i = 0; i < character; i++ ) cout << " ";
        cout << "^" << endl;
        cout  << "Your input contains illegal character" << endl
              << "type .ttg help to get more info" << endl;
        return true;
      }
    }
  }
  
  return false;  
}

bool Generator::isValid( string input ){
  int openedBrackets = 0;
  int totalAtoms = 0;
  int totalOperators = 0;
  for( int character = 0; character < input.length(); character++ ){
    if( IS_ATOM( input[ character ] ) ){
      totalAtoms++;
    }else if( find( m_binaryOperators.begin(), m_binaryOperators.end(), input[ character ]) != m_binaryOperators.end() ){
      totalOperators++;
    }else if( input[ character ] == OPENING_BRACKET ){
      openedBrackets++;
    }else if(input[ character ] == CLOSING_BRACKET ){
      openedBrackets--;
    }
    if( openedBrackets < 0 ){
      for( int i = 0; i < character; i++ ) cout << " ";
      cout << "^" << endl;
      cout  << "One of your brackets does not have an opening bracket" << endl;
      return true;
    }
  }
  if( totalAtoms - 1 != totalOperators ){
    cout << "atoms: " << totalAtoms << ", operators: " << totalOperators << endl;
    cout << "Some Atoms are missing an operator!" << endl;
    return true;
  }
  if( openedBrackets ){
    cout << "Some of the brackets aren't closed!" << endl;
    return true;
  }
  return false;
}

bool Generator::findAtoms(){
  for( auto character : m_formula ){
    if( character >= 'a' && character <= 'z' )
      if( find( m_atoms.begin(), m_atoms.end(), pair<char, bool>(character, false) ) == m_atoms.end() )
        m_atoms.push_back( pair<char, bool>(character, false) );
  }
  return m_atoms.size();
}

void Generator::printVSeparator( char sep ) const {
  for( int i = 0; i < m_atoms.size(); i++ ){
    cout << sep << sep;
  }
  for( int i = 0; i < m_formula.length(); i++ ){
    cout << sep;
  }
  cout << sep << sep << endl;
}

void Generator::printHSeparator() const {
  cout << "| ";
}

void Generator::printAtoms() const {
  for( auto atom : m_atoms )
    cout << atom.first << " ";
}