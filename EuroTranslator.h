#include <list>
#include <iostream>
#include <fstream>
#include "Utility.h"

using namespace std;
class EuroTranslator
{
private:
   Utility util;
   list<char> charList;

   bool isSoft(const list<char>::iterator inputItr);
   bool checkChar(const list<char>::iterator inputItr, char inputChar);
   bool checkPair(const list<char>::iterator secItr, char firstCh, char secCh);
   bool checkDuplicate(const list<char>::iterator firstItr);
   void replaceChar(list<char>::iterator inputItr, char replacement);
   void replacePair(list<char>::iterator secondItr, char replacement);
   void replaceDuplicate(list<char>::iterator firstItr);
   void removeEFromED(const list<char>::iterator itrOfD);
   bool checkWordLength(const list<char>::iterator inputItr, int minLength);
   bool nextCharIsWhitespace(const list<char>::iterator inputItr);
   void addWhitespaceToEndOfFile();

public:
   void convertToEuro();
   bool loadList(const char* filename);
   void printList();
};
