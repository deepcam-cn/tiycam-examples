#include <iostream>
#include <unistd.h>
int main() {
   /*Print hello world for IPK demo*/
   for(int i = 0; i < 20; i++)
   {
      std::cout << i  <<": Hello, World!" << std::endl;
      sleep(2);
   }
   
   return 0;
}