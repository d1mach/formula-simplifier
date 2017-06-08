#ifndef PTNODE_H
# define PTNODE_H

#include <ostream>
#include <list>

#ifdef DEBUG
# include "debug.h"
#else
# include "nodebug.h"
#endif //DEBUG

using namespace std;

namespace li_formula {

    typedef int atom_type;

    class ParseTreeNode {
    public:
	enum node_type {
	    T_ATOM, T_TRUE, T_FALSE, T_OR, T_AND, T_NOT, T_OROR, T_ANDAND };

	typedef enum node_type NodeType;
	typedef ParseTreeNode *pointer;
	typedef const ParseTreeNode *const_pointer;
	typedef const ParseTreeNode& const_reference;
	typedef ParseTreeNode& reference;
      
    protected:
	NodeType nodeType;
	ParseTreeNode(NodeType t) : nodeType(t) {
	    CALL("ParseTreeNode::ParseTreeNode");
	}
	~ParseTreeNode(){
	    CALL("ParseTreeNode::~ParseTreeNode");
	}
	friend ostream& operator << (ostream&, const_reference n);
    public:
	NodeType getNodeType() const { return nodeType; }
	bool isnode(NodeType t) const { return nodeType == t; }
	static void destroy(pointer);
    };

    class AtomNode : public ParseTreeNode {
	atom_type _atom;
    public:
	AtomNode(const atom_type& a) : ParseTreeNode(T_ATOM), _atom (a) { 
	    CALL("AtomNode::AtomNode");
	}
	~AtomNode(){
	    CALL("AtomNode::~AtomNode");
	}
	const atom_type& atom() const {return _atom;}
	friend ostream& operator << (ostream&, const_reference n);
	friend void ParseTreeNode::destroy(pointer);
    };

    class OrNode : public ParseTreeNode {
	const_pointer _left, _right;
    public:
	OrNode(const_pointer a, const_pointer b) : 
	    ParseTreeNode(T_OR), _left(a), _right(b) {
	    CALL("OrNode::OrNode");
	}
	~OrNode() {
	    CALL("OrNode::~OrNode");
	}

	const_pointer left() const {return _left; }
	const_pointer right() const {return _right; }

	friend ostream& operator << (ostream&, const_reference);
	friend void ParseTreeNode::destroy(pointer);
    };

    class AndNode : public ParseTreeNode {
	const_pointer _left, _right;
    public:
	AndNode(const_pointer a, const_pointer b) : 
	    ParseTreeNode(T_AND), _left(a), _right(b) {
	    CALL("AndNode::AndNode");
	}
	~AndNode() {
	    CALL("AndNode::~AndNode");
	}

	const_pointer left() const {return _left; }
	const_pointer right() const {return _right; }

	friend ostream& operator << (ostream&, const ParseTreeNode& n);
	friend void ParseTreeNode::destroy(pointer);
    };

    class OrOrNode : public ParseTreeNode {
    public:
	list<const_pointer> atoms;
	list<const_pointer> nonatoms;
    public:
	OrOrNode() : ParseTreeNode(T_OROR) {
	    CALL("OrOrNode::OrOrNode");
	}
	~OrOrNode() {
	    CALL("OrOrNode::~OrOrNode");
	}
	void add_atom(const_pointer a){
	    atoms.push_front(a);
	}	
	void add_nonatom(const_pointer a){
	    atoms.push_front(a);
	}
	friend ostream& operator << (ostream&, const ParseTreeNode& n);
	friend void ParseTreeNode::destroy(pointer);
    };

	namespace li_formula_private {
		typedef AtomNode ATOM;
		typedef OrNode OR;
		typedef OrOrNode OROR;
		typedef AndNode AND;
	}
  
	
    typedef ParseTreeNode PTNODE;

    void collect(PTNODE::const_pointer, OrOrNode*); 
    void collectAndDestroy(PTNODE::pointer, OrOrNode*);
    PTNODE::pointer flattenInPlace(PTNODE::pointer);
    PTNODE::pointer flatten(PTNODE::const_pointer);
}

#endif //PTNODE_H
