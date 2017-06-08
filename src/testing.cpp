#include <ostream.h>
#include "formulaParseTree.cpp"

using namespace li_formula;

void proba1(){
  AtomNode one(1);
  AtomNode two(2);
  AtomNode three(3);
  AtomNode four(4);
  OrNode a(&one, &two);
  OrNode b(&three, &four);
  AndNode x(&a,&b);
  cout << x << endl;
}

int main(){
  proba1();
  
  exit(0);
}
