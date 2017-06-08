#include <iostream.h>
#include "tokenizer.cpp"

using namespace li_formula;

typedef StringTokenizer ST;

void print_token(ST::token_type t, ST& tok){
    switch(t){
    case ST::ident_token: {
	char* n = new char[257];
	tok.readname(n,256);
	cout << n; 
	delete[] n;
	} break;
    case ST::number_token:
	cout << tok.readnumber();
	break;
    case ST::asterisk:
	cout << "*";
	break;
    case ST::plus_token:
	cout << "+";
	break;
    case ST::obracket:
	cout << "(";
	break;
    case ST::cbracket:
	cout << ")";
	break;
    default: ;
    };
}

void proba6(){
    ST strtokenizer("what*am * i+ ( 75 + to) + you?");
    ST::token_type t;
    

    t = strtokenizer.next_token();
    print_token(t,strtokenizer);
    
    while (strtokenizer.good()){
	cout << ",";
	t = strtokenizer.next_token();
	print_token(t,strtokenizer);
    }

    cout << endl;
}

int main(){
    
    proba6();

    exit(0);
}

