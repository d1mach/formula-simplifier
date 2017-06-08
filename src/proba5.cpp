#include <iostream.h>
#include "li_tokenizer.cpp"

void print_token(token_type t){
    switch(t){
    case ident_token: {
	char* n = getname();
	cout << n; 
	delete n;
	} break;
    case number_token:
	cout << getnumber();
	break;
    case asterisk:
	cout << "*";
	break;
    case plus_token:
	cout << "+";
	break;
    case obracket:
	cout << "(";
	break;
    case cbracket:
	cout << ")";
	break;
    default: ;
    };
}

int main(){
    start_tokenizer("what*am * i+ ( 75 + to) + you?");
    token_type t;
    
    t = next_token();
    
    print_token(t);

    t = next_token();

    while(t != end_token && t != error_token) {

	cout << ",";
	print_token(t);
	t = next_token();
    }
    
    cout << endl;

    exit(0);
}

