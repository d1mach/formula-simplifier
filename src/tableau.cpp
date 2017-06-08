#include "formulaParseTree.cpp"
#include "refcountedlist.cpp"

namespace li_formula {
    class Tableau {
    public:
		typedef list<atom_type> conjunction_type;
		typedef conjunction_type* pointer;
    private:
		class Branch {
		public:
			conjunction_type C;
			RCLIST L;
			Branch(PTNODE::const_reference );
			Branch(conjunction_type, RCLIST& );
		};

		list<Branch*> branches;
		
		pointer _next;
		
		void generate();
		void dispatch_node(PTNODE::const_reference,
				   conjunction_type& c,
				   RCLIST& L);
		bool entails(conjunction_type &c,
			     list<PTNODE::const_pointer>::const_iterator i,
			     list<PTNODE::const_pointer>::const_iterator j);
		void makebranches(const OrOrNode&,
						  conjunction_type& c,
						  RCLIST& L);
    public:
		Tableau(PTNODE::const_reference a){ 
			CALL("Tableau::Tableau");
			
			branches.push_front(new Branch(a));

			generate();
		}
		pointer next() { 
			CALL("Tableau::next");

			pointer temp = _next; 
			generate(); 
			return temp; 
		}
		bool empty() const { return _next == 0; }

    };

	inline Tableau::Branch::Branch(PTNODE::const_reference a){
		CALL("Branch::Branch");
		L.push_front(a);
	}
	inline Tableau::Branch::Branch(conjunction_type c, RCLIST& l) :
		C(c) {
		CALL("Branch::Branch");
		L.link(l);
	}
}
