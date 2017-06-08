#include "formulaParseTree.cpp"

using namespace li_formula;

int proba3(){
    AtomNode one(1);
    AtomNode two(2);
    AtomNode three(3);
    AtomNode four(4);

    OrNode a(&one,&two);
    AndNode b(&three,&three);
    OrNode c(&b,&a);
    AndNode d(&c,&four);

    cout << d << endl;

    PTNODE* p = flatten(&d);
  
    cout << *p << endl;

    PTNODE::destroy(p);

    return 0;
}

int main(){

    proba3();

    exit(0);
}
