

#include <iostream>
#include "FQueue.h"
using namespace std;


int main()
{
  //tworzymy kolejke i 5 elementow
  FQueue Kolejka;
  FQINFO* el_1 = new FQINFO( 1, 5, 10 );
  FQINFO* el_2 = new FQINFO( 2, 10, 20 ); 
  FQINFO* el_3 = new FQINFO( 3, 15, 30 );
  FQINFO* el_4 = new FQINFO( 4, 20, 40 ); 
  FQINFO* el_5 = new FQINFO( 5, 25, 50 ); 

  // dodajemy elementy do kolejki 
  Kolejka.FQEnqueue( el_1 );
  Kolejka.FQEnqueue( el_2 );
  Kolejka.FQEnqueue( el_3 );
  Kolejka.FQEnqueue( el_4 );
  Kolejka.FQEnqueue( el_5 );


  // wypisujemy kolejke
  cout<< "Kolejka z 5 elementami: " << endl;  
  Kolejka.FQPrintQ(); 
  cout << endl;


  // usuwamy element z kolejki 
  FQINFO* usuniety_el = Kolejka.FQDequeue();
  cout << "Usunieto element: " << *usuniety_el << endl; 

 // wypisujemy kolejke po usunieciu elementu  
  cout << "Kolejka po usunieciu elementu: " << endl;
  Kolejka.FQPrintQ();

  // usuwamy reszte elementow z kolejki 
  FQINFO* usuniety_el2 = Kolejka.FQDequeue();
  cout << "Usunieto element: " << *usuniety_el2 << endl;  

  FQINFO* usuniety_el3 = Kolejka.FQDequeue();
  cout << "Usunieto element: " << *usuniety_el3 << endl;

  FQINFO* usuniety_el4 = Kolejka.FQDequeue();
  cout << "Usunieto element: " << *usuniety_el4 << endl;
 
  FQINFO* usuniety_el5 = Kolejka.FQDequeue();
  cout << "Usunieto element: " << *usuniety_el5 << endl;

  //sprawdza czy kolejka jest pusta
  if( Kolejka.FQEmpty() )
  {
    cout << "Kolejka jest pusta" << endl;
  }
  else
  {
    cout << "Kolejka nie jest pusta" << endl;
  }
  
  try
  {
    // probujemy usunac element z pustej kolejki
    FQINFO* usuniety_el6 = Kolejka.FQDequeue();
    cout << "Usunieto element: " << *usuniety_el6 << endl;
  }
  catch( FifoException error )
  {
    cout<< error.getReason() << endl; 

  }

  // czyscimy kolejke 
  Kolejka.FQClear();

  return 0;


}

