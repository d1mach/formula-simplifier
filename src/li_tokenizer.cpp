
enum tok_type { 
    end_token = 0, ident_token, asterisk, plus_token, minus_token, number_token, 
    obracket, cbracket, osquare, csquare,
    ocurly, ccurly, arrow_token, assign_token,
    comma_token, error_token, ws_token
};

typedef enum tok_type token_type;

token_type next_token();

unsigned int getnumber();

char* getname();

void start_tokenizer(const char* pp);
