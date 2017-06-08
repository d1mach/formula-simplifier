#ifndef ROLLING_H
# define ROLLING_H

#include "formulaParseTree.cpp"

namespace li_formula {

  PTNODE* flatten(const PTNODE* n){
	CALL("flatten");

	using namespace li_formula_private;

	switch(n->getNodeType()){

	case PTNODE::T_AND:{
	  const AND& andnode = static_cast<const AND&>(*n);
	  const PTNODE *a, *b;

	  a = flatten(andnode.left());
	  b = flatten(andnode.right());
	  
	  if (andnode.right()->isnode(PTNODE::T_ATOM)){
		return new AND(b,a);
	  } else {
		return new AND(a,b);
	  }

	} break;

	case PTNODE::T_OR: {

	  OROR *p = new OROR();
	  collect(n, p);
	  
	  return p;

	} break;
	case PTNODE::T_ATOM: {
	  const ATOM& atomnode = static_cast<const ATOM&> (*n);
	  return new ATOM(atomnode.atom());
	} break;
	default: ;
	};
	return 0;
  }

    void collect(const PTNODE* n, OrOrNode* p){
	CALL("collect");

	using namespace li_formula_private;

	switch(n->getNodeType()){
	case PTNODE::T_AND: {
	  const AND& andnode = static_cast<const AND&> (*n);
	  const PTNODE *a, *b;

	  a = flatten(andnode.left());
	  b = flatten(andnode.right());
	  p->add_nonatom(new AND(a,b));
	  } break;
	case PTNODE::T_OR: {
	  const OR& ornode = static_cast<const OR&>(*n);
	  collect(ornode.left(),p);
	  collect(ornode.right(),p);
	  } break;
	case PTNODE::T_ATOM:{
	  const ATOM& atomnode = static_cast<const ATOM&> (*n);
	  p->add_atom(new ATOM(atomnode.atom()));
	  } break;
	default: ;
	};
  }
}

#endif // ROLLING_H

