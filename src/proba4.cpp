#include "tableau.cpp"

using namespace li_formula;

void proba4() {
	
	using namespace li_formula_private;

	PTNODE::const_reference a = ATOM(12);
	
	Tableau t(a);

	if (!t.empty()){
		Tableau::pointer q = t.next();
		cout << q->front() ;
		delete q;
	}

	PTNODE *p = flatten(&a);

	Tableau t1(*p);
	
	if (!t1.empty()){
		Tableau::pointer q = t1.next();
		cout << q->front() ;
		delete q;
	}

	
}

int main(){
	proba4();
	exit(0);
}
