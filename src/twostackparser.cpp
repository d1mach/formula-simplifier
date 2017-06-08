
#include <list>
#include <assert.h>
#include "formulaParseTree.cpp"
#include "tokenizer.cpp"

using namespace std;

namespace li_formula {

    class TwostackParser : public tokenizer_common {

		typedef list<PTNODE*> exprstack;
		typedef list<token_type> opstack;
		typedef exprstack::iterator expriterator;
		typedef opstack::iterator opiterator;
	
		typedef struct { 
			token_type token;  
			unsigned int prec;} precedence_record;
		static precedence_record operator_table[]; 

		exprstack expressions; 
		opstack operators;

		Tokenizer& tokenizer;

    public:
		PTNODE* parse();
		TwostackParser(Tokenizer& );
        ~TwostackParser();
    private:
		unsigned int precedence(token_type);
		expriterator parse(expriterator, opiterator);
		void collapse(token_type,expriterator&,expriterator,
					  opiterator&,opiterator);
    };

    PTNODE* TwostackParser::parse() { 
		return *(parse(expressions.begin(), operators.begin()));}

    unsigned int TwostackParser::precedence(token_type t){
		for(int i = 0; operator_table[i].token != end_token; i++){
			if (operator_table[i].token == t) 
				return operator_table[i].prec;
		}
		return 0;
    }

    TwostackParser::precedence_record TwostackParser::operator_table[3] = { 
	    {asterisk, 200},
	    {plus_token, 100}, 
	    {end_token,0} };

    TwostackParser::expriterator TwostackParser::parse(expriterator expr_base, 
													   opiterator op_base){

		CALL("Parser::parse");

		expriterator exprtop = expr_base;
		opiterator optop = op_base;
		token_type t; 

		using namespace li_formula_private;

		while ( tokenizer.good()){
			t = tokenizer.next_token();
			switch(t){
			case number_token: {
				int n = tokenizer.readnumber();
				exprtop = expressions.insert(exprtop, new ATOM(n));
			} break;
			case ident_token: {
				char* n = new char[257];
				tokenizer.readname(n,256);
				exprtop = expressions.insert(exprtop, new ATOM(n[0]));
				delete[] n;
			} break;
			case asterisk:
			case plus_token:
				collapse(t,exprtop,expr_base,optop,op_base);
				optop = operators.insert(optop,t);
				break;
			case obracket: {
				exprtop = parse(exprtop,optop);
			} break;
			case cbracket:
				collapse(end_token,exprtop,expr_base,optop,op_base);
				return exprtop;
			default:
				assert(false);
			};
		}
		collapse(end_token,exprtop,expr_base,optop,op_base);
		return exprtop;
    }

    void TwostackParser::collapse(token_type op,
								  expriterator& etop, expriterator ebase,
								  opiterator &otop, opiterator obase){

		CALL("Parser::collapse");

		using namespace li_formula_private;

		if (otop == obase) 
			return;

		if (etop == ebase) 
			cerr << "expression stack is empty, while opstack is not";

		token_type op1 = *otop;

		if (! ( precedence(op) > precedence(op1) ) ){
			PTNODE* e1 = *etop;

			etop = expressions.erase(etop);
			PTNODE* e2 = *etop;
			etop = expressions.erase(etop);
			switch(op1){
			case asterisk:
				etop = expressions.insert(etop, new AND(e2,e1));
				break;
			case plus_token:
				etop = expressions.insert(etop, new OR(e2,e1));
				break;
			default:
				assert(false);
			}
			otop = operators.erase(otop);

			collapse(op,etop,ebase,otop,obase);
		}
    }

    TwostackParser::TwostackParser(Tokenizer &tok) : tokenizer(tok) {
		expressions.push_front(0);
		operators.push_front(end_token);
    }

    TwostackParser::~TwostackParser(){
        expressions.pop_front();
        operators.pop_front();
    }
}
