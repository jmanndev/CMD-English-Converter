#include <iostream>
#include "EuroTranslator.h"

const int FILENAME = 1;

void runProgram(const char *filename);

int main(int argc, char* argv[])
{
   std::cout << "\nEuro converter by J Mann\n";
   if (argc == 2)
      runProgram(argv[FILENAME]);
   else std::cout << "\nERROR - Invalid command line arguments. Expecting 1 arg for input file\n";
}

void runProgram(const char* filename)
{
   EuroTranslator euTrans;
   try
   {
      if (euTrans.loadList(filename))
      {
         euTrans.printList();
         euTrans.convertToEuro();
         euTrans.printList();
      }
   }
   catch (exception &ex)
   {
      std::cout << "\nERROR - Exception thrown\n" << ex.what() << "\n";
   }
}
