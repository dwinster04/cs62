#include <iostream>
#include <string>
#include "class1.h"
#include "class2.h"

using namespace std;

int main () {
  Class1 c1(3);
      
  Class2 c2("a s d f");
  
  cout << "Hello World" << endl;
  cout << c1.getX() << endl;
  cout << c2.getS() << endl;
}
