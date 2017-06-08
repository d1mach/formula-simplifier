#include <cstdlib>
#include <iostream>
#include "tokenizer.cpp"

#ifdef DEBUG
# include "debug.h"
#else 
# include "nodebug.h"
#endif

using namespace std;

namespace li_formula{

    namespace li_tokenizer_private{
	inline void assert(bool test) { if(!(test)) { 
	    cout << "Assertion failed in StringTokenizer\n"; 
	    exit(-1);
	} }
	inline bool LE(int a, int b) {return (a) <= (b); }
	inline bool LT(int a, int b) {return (a) < (b); }
    }

    StringTokenizer::StringTokenizer(const char* p) :
	skipping(false), strptr(p)
    {
	CALL("StringTokenizer::Tokenizer");

	dispatch_table = new token_type[256];
	init_table();
	lookahead = *strptr++; // cannot use next_char here
    }

    StringTokenizer::~StringTokenizer(){
	CALL("StringTokenizer::~Tokenizer");

	delete[] dispatch_table;
    }

    inline bool StringTokenizer::failed() const{
	using namespace li_tokenizer_private;

	assert ( LE(0,lookahead) && LT(lookahead,maxchar) );

	return dispatch_table[lookahead] == end_token ||
	    dispatch_table[lookahead] == error_token;
    }

    bool StringTokenizer::good() const {

	if (skipping) return false;

	return !failed();
    }

    StringTokenizer::size_type StringTokenizer::readname(char_vector v, 
							 unsigned int bufsize){
	unsigned char c = lookahead;
	unsigned int count = 0;
	
	while(dispatch_table[c] == number_token ||
	      dispatch_table[c] == ident_token){
	    v[count++] = c;
	    c = next_char();

	    if (count == bufsize - 1) break;
	}

	v[count] = 0;
	lookahead = c;
	
	skipping = false;
	return count;
    }

    unsigned int StringTokenizer::readnumber(){
	unsigned int x = 0;
	unsigned char c = lookahead;

	while(dispatch_table[c] == number_token){
	    x *= 10;
	    x += c - 0x30;
	    c = next_char();
	}

	lookahead = c;

	skipping = false;

	return x;
    }

    void StringTokenizer::skip_token(){
	
	using namespace li_tokenizer_private;

	unsigned char c = lookahead;
	
	switch(dispatch_table[c]){
	case ident_token:
	    while (dispatch_table[c] == ident_token ||
		   dispatch_table[c] == number_token)
		c = next_char();
	    break;
	case number_token:
	    while( dispatch_table[c] == number_token)
		c = next_char();
	    break;
	default:
	    assert(false);
	};

	lookahead = c;
	skipping = false;
    }

    StringTokenizer::token_type StringTokenizer::next_token(){

	if (skipping) { skip_token(); }
	
	token_type t = dispatch_table[lookahead];

	switch(t){
	case ident_token:
	case number_token:
	    skipping = true;
	    return t;
	case ws_token:
	    lookahead = next_char();
	    return next_token();
	case error_token: 
	    return error_token;
	case end_token:
	    return end_token;
	default:
	    lookahead = next_char();
	    return t;
	}
	return error_token;
    }
    

    void StringTokenizer::init_table(){
	 
	unsigned int i;

	for(i =0; i < 256; i++)
	    dispatch_table[i] = error_token;
	dispatch_table[0x2a] = asterisk;
	dispatch_table[0x2b] = plus_token;
	dispatch_table[0x2d] = minus_token;
	dispatch_table[0x28] = obracket;
	dispatch_table[0x29] = cbracket;
	dispatch_table[0x5f] = ident_token;
	dispatch_table[0] = end_token;
	for(i = 0x01; i < 0x21; i++)
	    dispatch_table[i] = ws_token;
	for(i = 0x30; i < 0x3a; i++)
	    dispatch_table[i] = number_token;
	for(i = 0x61; i < 0x7b; i++)
	    dispatch_table[i] = ident_token;
	for(i = 0x41; i < 0x5b; i++)
	    dispatch_table[i] = ident_token;

    }

    unsigned char StringTokenizer::next_char(){
	if ( !failed() ) 
	    return *strptr++;
	else return 0;
    }
}

/* 
   problems: 

   1. number may overflow unsigned int.

   2. there is no way to check why tokenizer is not good.

   3. tokenizer does not report errors, it simply stops talking to
   you, in this state next_token might help. If it does not then it is
   an error or the end of the source.

*/
