#pragma once
#include <iostream>
using namespace std;

#define FQINFO FQInfo
/* 
w global.h  zdef klase (strukt) FQInfo z polami
- int nKey,
- tablica dynamiczna p int-ów (dwuelementowa),
- konstr z param int
- wirt destr,
- operat <<
zdef stala preprocesora FQINFO jako struktura FQInfo*/

struct FQInfo
{

 
  FQInfo( int klucz = 0, int p1 = 0, int p2 = 0 );
  virtual ~FQInfo();

  friend ostream& operator << ( ostream& out, FQInfo& i );


private:

  int nKey;
  int* p;
};


//INLINE FUNCTIONS:


inline FQInfo :: FQInfo( int klucz, int p1, int p2 )
{
  this->nKey = klucz;
  this->p = new(nothrow) int[2];
  this->p[0] = p1;
  this->p[1] = p2;
}
inline FQInfo:: ~FQInfo()
{
  delete[] p;
}

 inline ostream& operator << ( ostream& out, FQInfo& i )
{
   out << " Klucz " << " ( " << i.nKey << " )" << " p1 = " << i.p[ 0 ] << ", p2 = " << i.p[ 1 ] << endl;
   return out;
}