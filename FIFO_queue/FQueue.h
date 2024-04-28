#pragma once
#include "global.h"
#define FIFO_ALLOCATION_ERROR  0x01
#define FIFO_QUEUE_EMPTY 0x04
#define OTHER_ERROR      0x10


/*
  skladowe (FifoItem )
- wsk m_pItem (wsk na FQINFO),
- wsk m_pNext (wsk na nastepny w kolejce)
tyko w metodach klasy FQueue mozna wykreowac obiekt FifoItem
konstr i destr inline
konstr z parametrem domyslnym (NULL) - wsk na FQINFO (uzywamy stalej preprocesora WSZEDZIE)*/
class FifoItem
{
  
private:
  FifoItem( FQINFO* info = NULL );
  virtual ~FifoItem();


  friend class FQueue;

private:

  FQINFO* m_pItem;
  FifoItem* m_pNext;

};

// INLINE FUNCTIONS:
inline FifoItem:: FifoItem( FQINFO* info ) 
{
  this->m_pItem = info;
  this->m_pNext = NULL;
}
inline FifoItem:: ~FifoItem()
{
  
}



/*
- dodac klase wyjatku FifoException tez w tym pliku naglowkowym
	class FifoException
	konstr FifoException( int errCode = OTHER_ERROR );
	metoda getReason();  implementacja inline

Klsa zawiera tylko konstruktor (inline) na bazie kodu bledu i metode inline
getReason() zwrajaca (switch()) odpowiedni string (const char*) opisujacy rodzaj bledu

*/

class FifoException
{
public:

	FifoException(int errCode = OTHER_ERROR);
	const char* getReason();


private:

	int ErrCode;

};



// INLINE FUNCTIONS:

inline const char* FifoException::getReason()
{
	switch (this->ErrCode)
	{
	case FIFO_ALLOCATION_ERROR: return "Allocation Error!"; break;
	case FIFO_QUEUE_EMPTY: return " Queue is Empty!"; break;
	default: return " Something other is wrong; Error!";

	}
}


inline FifoException::FifoException(int errCode)
{
	this->ErrCode = errCode;

}





/* 

Fifo (class FQueue) realizowany jako lista prosta (z glowa) z dwoma
wskaznikami (m_pHead, m_pTail)

 - konstruktor bez param
 - wirt destr
 - bool FQEmpty(), int FQEnqueue( FQINFO* ); FQINFO* FQDequeue();
   void  FQClear();
 - prywatna void  FQDel();
*/
class FQueue
{
public:
  FQueue();
  virtual ~FQueue();

  bool FQEmpty();
  int FQEnqueue( FQINFO* Info );
  FQINFO* FQDequeue();
  void FQClear();
  void FQPrintQ();



private:
  void FQDel();

private:

  FifoItem* m_pHead;
  FifoItem* m_pTail;

};



// INLINE FUNCTIONS:

inline bool FQueue::FQEmpty()
{
  return !m_pHead;
}

inline FQueue::FQueue()
{
	m_pHead = NULL;
	m_pTail = NULL;
}


inline FQueue:: ~FQueue()
{
	while (!FQEmpty())
	{
		FQDel();
	}
}




inline int FQueue::FQEnqueue(FQINFO* Info)
{
	FifoItem* newElement = new(nothrow) FifoItem(Info);

	if (!newElement)
	{
		throw FifoException(FIFO_ALLOCATION_ERROR);
	}

	if (FQEmpty())
	{
		m_pHead = m_pTail = newElement;
	}
	else
	{
		m_pTail->m_pNext = newElement;
		m_pTail = newElement;
	}

	return 0;
}

inline FQINFO* FQueue::FQDequeue()
{
	if (FQEmpty())
	{
		throw FifoException(FIFO_QUEUE_EMPTY);
	}

	FifoItem* pItem = m_pHead; // pobieramy wskaznik do pierwszego elementu 
	FQINFO* res = pItem->m_pItem;

	m_pHead = pItem->m_pNext; // phead wskazuje na nastepny element

	if (m_pHead == NULL)
	{
		m_pTail = NULL; // jesli m_pHead puste to ustawiamy pTail na NULL bo kolejka jest pusta 
	}

	delete pItem;

	return res;

}


inline void FQueue::FQClear()
{
	if (FQEmpty())
	{
		cerr << "Kolejka pusta" << endl;
	}
	while (!FQEmpty())
	{
		delete FQDequeue();

	}
}




inline void FQueue::FQDel()
{
	if (!FQEmpty())
	{
		FifoItem* pItem = m_pHead;
		m_pHead = pItem->m_pNext;
		delete pItem;
	}
	else
	{
		m_pTail = NULL;
	}
}





inline void FQueue::FQPrintQ()
{
	FifoItem* Item = m_pHead;

	if (FQEmpty())
	{
		throw FifoException(FIFO_QUEUE_EMPTY);
	}

	while (Item != m_pTail)
	{
		cout << *(Item->m_pItem);
		Item = Item->m_pNext;
	}

	cout << *(Item->m_pItem);


}




