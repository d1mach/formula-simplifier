#include "refcountedlist.cpp"
#include "formulaParseTree.cpp"

using namespace li_formula;

void proba2(){

	using namespace li_formula_private;

	ATOM zero(0);
	ATOM one(1);
	ATOM two(2);

	RefCountedList L;

	L.push_front(zero);
	L.push_front(one);
	L.push_front(two);

	RefCountedList L1;

	L1.link(L);

	while (!L.empty()){
		cout << L.front() << " ";
		L.pop_front();
	}

	for(RefCountedList::iterator i = L1.begin(); i != L1.end(); i++){
		cout << *i << " ";
	}

	while (!L1.empty()){
		cout << L1.front() << " ";
		L1.pop_front();
	}
}

int main(){
	proba2();
	exit(0);
}
