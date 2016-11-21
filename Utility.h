#include <list>
#include <iostream>
#include <string>

class Utility
{
public:
   std::string getListString(const std::list<char> &charList);
   unsigned short getHash(const std::list<char> &charList); 
};
