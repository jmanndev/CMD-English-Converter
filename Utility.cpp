#include "Utility.h"

std::string Utility::getListString(const std::list<char> &charList)
{
   std::list<char>::const_iterator itr;
   std::string tempString;
   for (itr = charList.begin(); itr != charList.end(); itr++)
      tempString = tempString + *itr;
   return tempString;
}

unsigned short Utility::getHash(const std::list<char> &charList)
{
   unsigned short shift, hash = 0;
   std::list<char>::const_iterator itr;
   for (itr = charList.begin(); itr != charList.end(); itr++)
   {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   return hash;
}
