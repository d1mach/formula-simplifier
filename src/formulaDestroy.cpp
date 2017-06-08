#ifndef FORMULA_DESTROY_H
# define FORMULA_DESTROY_H

#include "formulaParseTree.cpp"

namespace li_formula {

    void PTNODE::destroy(pointer n){
		CALL("PTNODE::destroy");

		using namespace li_formula_private;
	
		switch (n->getNodeType()){
		case PTNODE::T_AND:{

			AND& andnode = static_cast<AND&> (*n);
			destroy(const_cast<pointer>(andnode._left));
			destroy(const_cast<pointer>(andnode._right));

			delete &andnode;

		} break;
		case PTNODE::T_OR:{

			OR& ornode = static_cast<OR&> (*n);
			destroy(const_cast<pointer>(ornode._left));
			destroy(const_cast<pointer>(ornode._right));

			delete &ornode;

		} break;
		case PTNODE::T_OROR:{

			OROR& xnode = static_cast<OROR&> (*n);
			list<const_pointer>::iterator i = xnode.atoms.begin();
			while (i != xnode.atoms.end()) {
				const ATOM& a = static_cast<const ATOM&> (**i++);
				delete const_cast<ATOM*>(&a);
			}

			i = xnode.nonatoms.begin();
			while (i != xnode.nonatoms.end()) {
				destroy(const_cast<pointer>(*i++));
			}

			delete &xnode;

		} break;
		case PTNODE::T_ATOM:{
			ATOM& atomnode = static_cast<ATOM&> (*n);
			delete &atomnode;
		} break;
		default: ;
		};
    }

}

#endif // FORMULA_DESTROY
