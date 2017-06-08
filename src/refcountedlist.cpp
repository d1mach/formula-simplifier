#ifndef RCLIST_H
# define RCLIST_H

#include <stdio.h>

#ifdef DEBUG
# include "debug.h"
#else
# include "nodebug.h"
#endif //DEBUG

#include "formulaParseTree.cpp"

namespace li_formula {

  typedef ParseTreeNode ElementType;

  typedef unsigned int uint32;

  class RefCountedList {
  public:
	class iterator;
  private:
	class RefCountedListNode;
	typedef RefCountedList RCLIST;
	typedef RefCountedListNode RCNODE;
  private:
	typedef RefCountedListNode *nodeptr;
	nodeptr head;
  public:
	RefCountedList() : head(0) {
	  CALL("RCLIST::RCLIST");
	}
	RefCountedList(const RefCountedList& L){
	  CALL("RCLIST::RCLIST(RCLIST&)");
	  link(L);
	}

	~RefCountedList() {
	  CALL("RCLIST::~RCLIST");
	}
	iterator begin();
	bool empty () const;
	iterator end();
	const ElementType& front();
	void link(const RefCountedList &L);
	void push_front(const ElementType &a);
	void pop_front();
  };

  typedef RefCountedList RCLIST;

  class RCLIST::RefCountedListNode {
  private:
	typedef RefCountedListNode *nodeptr;
	friend RCLIST;
	friend RCLIST::iterator;

  private:
	uint32 refcount;
	nodeptr next;
	const ElementType& atom;

  public:
	RefCountedListNode(const ElementType &a,const nodeptr n) : 
	  refcount(1), next(n), atom(a) {
	  CALL("RCNODE::RCNODE");
	}
	~RefCountedListNode() {
	  CALL("RCNODE::~RCNODE");
	}
  };

  class RCLISTException {};

  class RCLIST::iterator {
	RCNODE* ptr;
  private:
	iterator(RCNODE* const h) : ptr(h) {}
	friend RCLIST;
  public:
	iterator& operator ++(){ ptr = ptr->next; return *this; }
	iterator& operator ++(int){ ptr = ptr->next; return *this; }
	const ElementType& operator *(){ return ptr->atom; }
	bool operator == (iterator i){ return ptr == i.ptr ; }
	bool operator != (iterator i){ return ptr != i.ptr ; }
  };

  inline RCLIST::iterator RCLIST::begin(){
	CALL("RCLIST::begin");
	return iterator(head);
  }

  inline bool RCLIST::empty() const {
	  CALL("RCLIST::empty");
	  return head == 0;
  }

  inline RCLIST::iterator RCLIST::end(){
	CALL("RCLIST::end");
	return iterator(0);
  }

  inline const ElementType& RCLIST::front(){
	CALL("RCLIST::front");
	return head->atom;
  }

  inline void RCLIST::link(const RCLIST &L){
	CALL("RCLIST::link");

	head = L.head;

	if (head)
	    head->refcount++;
  }

  inline void RCLIST::push_front(const ElementType &a){
	CALL("RCLIST::push_front");
	head = new RCNODE(a,head);
  }

  inline void RCLIST::pop_front(){
	CALL("RCLIST::pop_front");
	nodeptr next = head->next;
	if (--head->refcount == 0){
	  delete head;
	} else {
	  if (next){
		next->refcount++;
	  }
	}
	head = next;
  }

}

#endif //RCLIST_H
