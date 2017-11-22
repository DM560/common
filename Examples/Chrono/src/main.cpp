#include "chrono.h"

using namespace Chrono;
using namespace std;

int main () {
	Date d1{2018,Month(1),1};
	Date d2=d1;
	cout<<d2<<endl;
	keep_window_open();
}
