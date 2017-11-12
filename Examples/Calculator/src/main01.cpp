#include "../../std_lib_facilities.h"


//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
    :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
    :kind(ch), value(val) { }
    Token() = default;
};

//------------------------------------------------------------------------------
/*
Token get_token()    // read a token from cin
{
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
    
    switch (ch) {
        //not yet   case ';':    // for "print"
        //not yet   case 'q':    // for "quit"
        case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);        // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {    
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
        default:
        error("Bad token");
    }
}
*/



class Token_stream {
public:
	// user interface:
	Token get();		// get a Token
	void putback(Token); // put a Token back into the Token_stream
private:
	// representation: not directly accessible to users:
	bool full {false};	// is there a Token in the buffer?
	Token buffer;   // here is where we keep a Token put back using putback()
};



void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer=t;
	full=true;
}


Token Token_stream::get()	 // read a Token from the Token_stream
{
    // check if we already have a Token ready
    if (full) { full=false; return buffer; }  
    
    char ch;
    cin >> ch;  // note that >> skips whitespace (space, newline, tab, etc.)
    
    switch (ch) {
        case '(': case ')': case ';': case 'q': 
        case '+': case '-': case '*': case '/': 
        return Token{ch};           // let each character represent itself
        case '.': case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
        {	cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;		// read a floating-point number
            return Token{'8',val};	// let '8' represent "a number"
        }
        default:  error("Bad token");
    }
}


Token_stream ts;
//------------------------------------------------------------------------------

double expression();  // read and evaluate a Expression

//------------------------------------------------------------------------------

double term();        // read and evaluate a Term

//------------------------------------------------------------------------------

double primary()     // read and evaluate a Primary
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':    // handle '(' expression ')'
        {    
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
        default:
        error("primary expected");
    }
}



//------------------------------------------------------------------------------

int main() {
    try {
        double val=0;
        while (cin) {
            Token t = ts.get();
            if (t.kind=='q') break;
            if (t.kind==';')    
            cout << "=" << val << "\n";
            else
            ts.putback(t);
            val = expression();
        }
        keep_window_open("~0");
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        keep_window_open ("~1");
        return 1;
    }
    catch (...) {
        cerr << "exception \n";
        keep_window_open ("~2");
        return 2;
    }
    return 0;
}




//------------------------------------------------------------------------------

double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();     // get the next token
    while(true) {    
        switch(t.kind) {
            case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
            case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
            default:
            ts.putback(t);
            return left;       // finally: no more + or -: return the answer
        }
    }
}


//------------------------------------------------------------------------------

double term()
{
    double left = primary();
    Token t = ts.get();
    
    while(true) {
        switch (t.kind) {
            case '*':
            left *= primary();
            t = ts.get();
            break;
            case '/':
            {    
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
            default: 
            ts.putback(t);
            return left;
        }
    }
}


//------------------------------------------------------------------------------