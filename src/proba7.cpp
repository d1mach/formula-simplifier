#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "twostackparser.cpp"
#include "readline/readline.h"
#include "readline/history.h"
#include "string.h"
#include "tableau.cpp"
#include "pstatus.h"

using namespace std;
using namespace li_formula;

class stringpointer {
    typedef char* charpointer;
    char* p;
public:
    stringpointer() : p(0) {}
    char* operator =(char *ptr) { return p = ptr; }
    operator char*() { return p; }
    ~stringpointer(){ CALL("stingpointer::destructor"); delete p; }
};

void cnf(PTNODE& n){
    Tableau t(n);

    int ccount = 0;
    while (!t.empty()){
	Tableau::pointer q = t.next();
        //	cout << "[";
        //	copy(q->begin(),q->end(),ostream_iterator<atom_type>(cout," "));
        //	cout << "]" << endl;
	delete q;
	ccount++;
    }
    cout << endl << ccount << " conjunctions" << endl; 

}

void proba7(){



    char* formula0 = "2*(3  * 6+ 3 * 8)*(4+3)";
    char* formula1 = "(1*(2+3)*(4+5)*(6+7)*8*9*(10+11)*(9+12)*8*13*10*(13+14)*4*2*(15+16)*(15+11)*15*(17+18)*(19+20)*(21+22)*(23+24)*25*26*(27+28)*25*23)";
    char* formula2 = "(1*(2+3)*(4+5)*(6+7)*8*9*(10+11)*(9+12)*8*13*10*(13+14)*4*2*(15+16)*(15+11)*15*(17+18)*(19+20)*(21+22)*(23+24)*25*26*(27+28)*25*23*(29+30+31)*(32+33)*(34+35)*(36+37)*38*39*(40+41)*(39+42)*38*43*40*(43+44)*34*33*(45+46)*(45+41)*45*(47+48)*(49+50)*(51+52))";
    char* formula3 = "(1*(2+3)*(4+5)*(6+7)*8*9*(10+11)*(9+12)*8*13*10*(13+14)*4*2*(15+16)*(15+11)*15*(17+18)*(19+20)*(21+22)*(23+24)*25*26*(27+28)*25*23*(29+30+31)*(32+33)*(34+35)*(36+37)*38*39*(40+41))";

    add_history(formula2);
    add_history(formula3);
    add_history(formula0);
    add_history(formula1);

    stringpointer line;
    Timer t;
    line = readline(">> ");

    while (strcmp(line,"exit") != 0){

        add_history(line);

        Tokenizer tok(line);
        TwostackParser par(tok);
        PTNODE* pt = par.parse();

        cout << "using the original formula" << endl;

        cout << *pt << endl;

        t.start();
        
        cnf(*pt);
        
        t.stop();

        t.output(cout,Timer::user);
        cout << endl;

        cout << "using the preprocessed formula" << endl;

        t.start();

        PTNODE *pt1 = flatten(pt);
        
        PTNODE::destroy(pt);
    
        cout << *pt1 << endl;

        cnf(*pt1);

        t.stop();

        t.output(cout,Timer::user);
        cout << endl;

        PTNODE::destroy(pt1);
        
        line = readline (">> ");
    } 
}

int main(){
    proba7();
    exit(0);
}
