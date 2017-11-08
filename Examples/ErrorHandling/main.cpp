#include "../std_lib_facilities.h"

int main()
{
	try {
		int i = 0;
		while (i < 10) cout << ++i << endl;
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "unhandled" << endl;
		keep_window_open();
		return 1;
	}
}
