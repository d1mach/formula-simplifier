#include "assert.h"

class LIFormula2 {
    enum Connective _con;
    typedef LinearInequality* atom_type;
    class Node;
    Node* impl;
public:
    LIFormula2(atom_type liptr);
    LIFormula2(enum Connective con, LIFormula2* a, LIFormula2* b);
    LIFormula2(enum Connective con);
    enum Connective con(){ return _con;}
    LIFormula2* left();
    LIFormula2* right();
    atom_type atom();
    void output(ostream&);
    LIFormula2* simplify();
    void destroy();

public:
    class SLIGenerator{
    public:
	SLIGenerator(LIFormula2* );
	SLIGenerator(LIFormula2*, SLI*);
	~SLIGenerator();
	SLI* next();
	bool more();
    }
};

class ATOM : public LIFormula2::Node {
    atom_type _atom; 
public:
    ATOM(atom_type liptr) : _atom(liptr);
    atom_type atom(){ return _atom; }
};

class AND : public LIFormula2::Node {
    LIFormula2 *_left, *_right;
public:
    AND(LIFormula2 *a, LIFormula2 *b) : _left(a), _right(b) {}
    LIFormula2* left() {return _left;}
    LIFormula2* right() {return _right;}
};

class OR : public LIFormula2::Node {
    LIFormula2 *_left, *_right;
public:
    OR(LIFormula2 *a, LIFormula2 *b) : _left(a), _right(b) {}
    LIFormula2* left() {return _left;}
    LIFormula2* right() {return _right;}
}

LIFormula2::LIFormula2(atom_type liptr) : _con(T_ATOM){
    impl = new ATOM(liptr);
}

LIFormula2::LIFormula2(enum Connective con, LIFormula2 *a, LIFormula2 *b) :
    _con(con) {
    switch(con){
    case T_AND:
	impl = new AND(a,b);
	break;
    case T_OR:
	impl = new OR(a,b);
	break;
    default:
	assert(false);
    }
}

LIFormula2::LIFormula2(enum Connective con) : _con(con){}

LIFormula2* LIFormula2::left(){
    switch(_con){
    case T_AND: {
        AND& and = static_cast<AND&>(*impl);
	return and.left();
    }
    case T_AND:{
        OR& or = static_cast<OR&>(*impl);
	return or.left();
    }
    default:
	assert(false);
    }
}

LIFormula2* LIFormula2::right(){
    switch(_con){
    case T_AND: {
        AND& and = static_cast<AND&>(*impl);
	return and.right();
    }
    case T_AND:{
        OR& or = static_cast<OR&>(*impl);
	return or.right();
    }
    default:
	assert(false);
    }
}

atom_type LIFormula2::atom(){
    ATOM& atom = static_cast<ATOM&>(*impl);
    return atom.atom();
}

LIFormula2* LIFormula2::simplify(){ return this; }
