#include <iostream>
#include <list>

#include "refcountedlist.cpp"
#include "formulaParseTree.cpp"

using namespace std;
using namespace li_formula;

typedef struct generatorContext {
  list<atom_type> B;
  RCLIST L;
} GeneratorContext;

slist<GeneratorContext> generator;

int main(){

	using namespace li_formula_private;

  cout << "That's a proba\n";

  const ATOM& a = ATOM(0);
  const ATOM& b = ATOM(1);
  const ATOM& c = ATOM(2);
  const ATOM& d = ATOM(3);
  const OR& ab = OR(&a,&b);
  const OR& cd = OR(&c,&d);

  const AND& F = AND(&ab,&cd);
  struct generatorContext g = { slist<atom_type>(), RCLIST() };
  g.L.push_front(F);
  if (!g.L.empty()) {
    const PTNODE& F = g.L.front();
    cout << F << endl;
    g.L.pop_front();
  }
  exit(0);
}

