#include "formulaParseTree.cpp"
#include "refcountedlist.cpp"
#include "tableau.cpp"

namespace li_formula {

    template <class T> inline T& fetch_next(list<T*>& L){
	T* temp = L.front();
	L.pop_front();
	return *temp;
    }
		
    void Tableau::generate(){
	CALL("Tableau::generate");

	if (branches.empty()) { _next = 0; return; }

	Branch& current_branch = fetch_next<Branch>(branches);

	conjunction_type& c = current_branch.C;
	RCLIST& L = current_branch.L;

	while (! L.empty()) {
			
	    PTNODE::const_reference n = L.front();
			
	    L.pop_front();

	    dispatch_node(n,c,L);

	    /* 
	       if (c is inconsistent) 
	       {destroy this branch and fetch new branch} 
	       {if there are no branches left return 0; }
	    */
	}

	_next = new conjunction_type(c); 
	delete &current_branch; 
	return;

    }

    void Tableau::dispatch_node(PTNODE::const_reference n, 
				conjunction_type& c,
				RCLIST& L){
		
	CALL("Tableau::dispatch_node");

	using namespace li_formula_private;

	switch(n.getNodeType()){
	case PTNODE::T_ATOM:{
	    const ATOM& atomnode = static_cast<const ATOM&>(n);
	    c.push_front(atomnode.atom());
	} break;
	case PTNODE::T_OR: {
	    const OR& ornode = static_cast<const OR&>(n);
	    Branch* b = new Branch(c,L);

	    L.push_front(*ornode.left());
	    b->L.push_front(*ornode.right());

	    branches.push_front(b); // copy
	} break;
	case PTNODE::T_AND: {
	    const AND& andnode = static_cast<const AND&>(n);
	    L.push_front(*andnode.right());
	    L.push_front(*andnode.left());
	} break;
	case PTNODE::T_OROR: {
	    const OROR& xnode = static_cast<const OROR&>(n);
	    if (entails(c,xnode.atoms.begin(),xnode.atoms.end())) break;
	    else makebranches(xnode,c,L);
	} break;
	default: ;
	};
    }

    void Tableau::makebranches(const OrOrNode& xnode,
			       conjunction_type& c,
			       RCLIST& L){
	CALL("Tableau::makebranches");

	list<PTNODE::const_pointer>::const_iterator i,j;
				
	PTNODE::const_pointer top;
	RCLIST* p;

	j = xnode.nonatoms.begin();

	if (! xnode.atoms.empty()){
	    i = xnode.atoms.begin();
	    top = *i++;
	    while(i != xnode.atoms.end()){
		p = new RCLIST();
		p->link(L);
		p->push_front(**i++);
		branches.push_front(new Branch(c,*p)); 
	    }
	} else {
	    top = *j++;
	}

	while(j != xnode.nonatoms.end()){
	    p = new RCLIST();
	    p->link(L);
	    p->push_front(**j++);
	    branches.push_front(new Branch(c,*p)); 
	}
				
	L.push_front(*top);

    }

    bool Tableau::entails(conjunction_type &c,
			  list<PTNODE::const_pointer>::const_iterator i,
			  list<PTNODE::const_pointer>::const_iterator j){

	using namespace li_formula_private;

	while(i != j){
	    conjunction_type::iterator k = c.begin();
	    while(k != c.end()){
		if ( (*i)->getNodeType() == PTNODE::T_ATOM){
		    const ATOM &atomnode = static_cast<const ATOM&>(**i);
		    if (atomnode.atom() == *k) return true;
		}
		k++;
	    }
	    i++;
	    /* if c entails i return true */
	}
	return false;
    }
}

