#include "formulaParseTree.cpp"

namespace li_formula {

    ostream& operator << (ostream& s, const ParseTreeNode& n){
		
		using namespace li_formula_private;

		switch(n.nodeType) {
		case PTNODE::T_AND: {
			const AND &andnode = static_cast<const AND&>(n);
			return s << "(" << *(andnode._left) << " & " 
					 << *(andnode._right) << ")";
		} break;
		case PTNODE::T_OR: {
			const OR &ornode = static_cast<const OR&>(n);
			s << "(" << *(ornode._left) << " | " << *(ornode._right) << ")";
		} break;
		case PTNODE::T_ATOM: {
			const ATOM &atom = static_cast<const ATOM&>(n);
			s << atom.atom() ;
		} break;
		case PTNODE::T_OROR: {
			const OROR &xnode = static_cast<const OROR&>(n);
			s << "(";
			list<PTNODE::const_pointer>::const_iterator i = xnode.atoms.begin();
			if (i != xnode.atoms.end())
				s << **i++;
			while ( i != xnode.atoms.end())
				s << " | " << **i++;
			i = xnode.nonatoms.begin();
			while (i != xnode.nonatoms.end())
				s << " | " << **i++;
			s << ")";
		} break;
		default:;
		};
		return s;
    }

}
