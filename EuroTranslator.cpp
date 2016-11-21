#include "EuroTranslator.h"

void EuroTranslator::convertToEuro()
{
   bool changeMade;
   list<char>::iterator itr;
   for (itr = charList.begin(); itr != charList.end(); itr++)
   {
      changeMade = true;
      while (changeMade)
      {
         changeMade = true;
         if (checkChar(itr, 'w'))
            replaceChar(itr, 'v');
         else if (isalpha(*itr) && checkDuplicate(itr))
            replaceDuplicate(itr);
         else if (checkPair(itr, 'p', 'h'))
            replacePair(itr, 'f');
         else if (checkPair(itr, 't', 'h'))
            replacePair(itr, 'z');
         else if (checkPair(itr, 'o', 'u'))
            replacePair(itr, 'u');
         else if (checkPair(itr, 'e', 'a'))
            replacePair(itr, 'e');
         else if (checkChar(itr, 'c'))
         {
            if (isSoft(itr)) replaceChar(itr, 's');
            else replaceChar(itr, 'k');
         }
         else if (!isalnum(*itr) && checkPair(itr, 'e', *itr) && checkWordLength(itr, 4))
            replacePair(itr, *itr);
         else if (checkPair(itr, 'e', 'd') && nextCharIsWhitespace(itr))
            removeEFromED(itr);
         else changeMade = false;
      }
   }
}

void EuroTranslator::removeEFromED(const list<char>::iterator itrOfD)
{
   if (itrOfD != charList.begin())
   {
      list<char>::iterator itr = itrOfD;
      advance(itr, -1);
      charList.erase(itr);
   }
}

bool EuroTranslator::nextCharIsWhitespace(const list<char>::iterator inputItr)
{
   if (inputItr != charList.end())
   {
      list<char>::iterator itr = inputItr;
      advance(itr, 1);
      if (!isalnum(*itr))
      {
         return true;
      }
   }
   return false;
}

void EuroTranslator::replaceChar(list<char>::iterator inputItr, char replacement)
{
   if (isupper(*inputItr)) *inputItr = toupper(replacement);
   else *inputItr = tolower(replacement);
}

void EuroTranslator::replacePair(list<char>::iterator secondItr, char replacement)
{
   if (secondItr != charList.begin())
   {
      list<char>::iterator itr = secondItr;
      advance(itr, -1);
      if (isupper(*itr)) *secondItr = toupper(replacement);
      else *secondItr = tolower(replacement);
      charList.erase(itr);
   }
}

void EuroTranslator::replaceDuplicate(list<char>::iterator firstItr)
{
   if (firstItr != charList.end())
   {
      list<char>::iterator secondItr = firstItr;
      advance(secondItr, 1);
      charList.erase(secondItr);
   }
}

bool EuroTranslator::checkChar(const list<char>::iterator inputItr, char inputChar)
{
   return tolower(*inputItr) == tolower(inputChar);
}

bool EuroTranslator::checkPair(const list<char>::iterator secItr, char firstCh, char secCh)
{
   if (checkChar(secItr, secCh) && secItr != charList.begin())
   {
      list<char>::iterator itr = secItr;
      advance(itr, -1);
      if (checkChar(itr, firstCh))
         return true;
   }
   return false;
}

bool EuroTranslator::checkDuplicate(const list<char>::iterator firstItr)
{
   if (checkChar(firstItr, *firstItr) && firstItr != charList.end())
   {
      list<char>::iterator secondItr = firstItr;
      advance(secondItr, 1);
      if (checkChar(secondItr, *firstItr))
         return true;
   }
   return false;
}

void EuroTranslator::printList()
{
   cout << util.getListString(charList);
   cout << "\nHash = " << util.getHash(charList) << '\n';
}

bool EuroTranslator::loadList(const char* filename)
{
   char tempChar;
   ifstream myFile;
   bool loadStatus = false;

   myFile.open(filename);
   if (myFile.is_open())
   {
      while (myFile >> noskipws >> tempChar)
         charList.push_back(tempChar);

      if (charList.size() != 0)
      {
         loadStatus = true;
         addWhitespaceToEndOfFile();
      }
      else cout << "\nERROR - File is empty\n";
   }
   else cout << "\nERROR - Unable to load '" << filename << "'\n";
   return loadStatus;
}

void EuroTranslator::addWhitespaceToEndOfFile()
{
   list<char>::iterator itr = charList.end();
   bool addWhitespace = true;

   if (charList.size() < 2)
      charList.push_back('\n');
   while (itr != charList.begin() && addWhitespace)
   {
      itr = charList.end();
      advance(itr, -1);
      if (checkChar(itr, '\n'))
         addWhitespace = false;
      else charList.push_back('\n');
   }
}

bool EuroTranslator::checkWordLength(const list<char>::iterator inputItr, int minLength)
{
   int counter = 0;
   if (inputItr != charList.begin()) {
      list<char>::iterator itr = inputItr;
      do
      {
         counter++;
         advance(itr, -1);
      } while (counter < minLength + 1 && isalnum(*itr) && itr != charList.begin());
      if (itr == charList.begin())
         counter++; //accounts for loop ending one step early if it hits ".begins()"
   }
   return counter > minLength;
}

bool EuroTranslator::isSoft(const list<char>::iterator inputItr)
{
   if (inputItr != charList.end())
   {
      list<char>::iterator itr = inputItr;
      advance(itr, 1);
      return checkChar(itr, 'e') || checkChar(itr, 'i') || checkChar(itr, 'y');
   }
   else return false;
}
