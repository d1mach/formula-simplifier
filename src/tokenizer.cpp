namespace li_formula{

    class tokenizer_common {
    public:
	enum tok_type { 
	    end_token = 0, ident_token, asterisk, 
	    plus_token, minus_token, number_token, 
	    obracket, cbracket, osquare, csquare,
	    ocurly, ccurly, arrow_token, assign_token,
	    comma_token, error_token, ws_token
	};

	typedef enum tok_type token_type;
    };

    class StringTokenizer : public tokenizer_common {
    private:
	static const unsigned int maxchar = 255;
	static const unsigned int maxint10 = 0xfffffff;
    public:
	typedef unsigned int size_type;
	typedef char char_vector[];

    private:
	bool skipping; /* ??? */
	char lookahead;
	token_type* dispatch_table;
	//	token_type current_token;

	void init_table();
	void skip_token();
	bool failed() const;

	const char *strptr;
	unsigned char next_char();

    public:
	StringTokenizer(const char*);
	~StringTokenizer();
	bool good() const;
	size_type readname(char_vector, unsigned int);
	unsigned int readnumber();
	token_type next_token();
    };

    typedef StringTokenizer Tokenizer;

}
