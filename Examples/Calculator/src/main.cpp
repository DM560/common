#include "../../std_lib_facilities.h"


class Token {
public:
	char kind;
	double value;
};

double expression()	// read and evaluate: 1   1+2.5   1+2+3.14  etc.
{
  double left = term(); 		// get the Term
  while (true) {
    Token t = get_token();	// get the next token...
    switch (t.kind) {	// ... and do the right thing with it
      case '+':     left += term(); break;
      case '-':     left -= term(); break;
      default:      return left;	// return the value of the expression
    }
  }
}





double term()	// exactly like expression(), but for * and  /
{
  double left = primary(); 		// get the Primary
  while (true) {
    Token t = get_token();	// get the next Token
    switch (t.kind) {	
      case '*':     left *= primary();	break;
      case '/':
      {	double d = primary();
	if  (d==0) error("divide by zero");
	left /= d;
	break;
      }
      default:	    return left;	// return the value
    }
  }
}

double primary()	// Number or '(' Expression ')'
{
  Token t = get_token();
  switch (t.kind) {
    case '(':			       // handle '('expression ')'
    {	double d = expression();
      t = get_token();
      if (t.kind != ')') error("')' expected");
      return d;
    }
    case '8':		// we use '8' to represent the ``kind'' of a number
    return t.value;	// return the number's value
    default:
    error("primary expected");
  }
}

int main()
try {
  while (cin)
  cout << expression() << '\n';
  keep_window_open();		// for some Windows versions
}
catch (runtime_error& e) {
  cerr << e.what() << endl;
  keep_window_open ();
  return 1;
}
catch (...) {
  cerr << "exception \n";
  keep_window_open ();
  return 2;
}
