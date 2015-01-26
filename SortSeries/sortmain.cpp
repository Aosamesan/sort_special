#include"sort.h"

using namespace Painter;
using namespace Sorts;

int main(){
	cout << "Press Enter Key to Start... ";
	getchar();
	
	FramePainter f;
	PrintSorter ps;
	unsigned int sizes[] = { 5000, 10000, 30000, 50000, 100000, 500000, 1000000 };
	
	cout << f.top() << endl;
	cout << f.header() << endl;
	for (unsigned int i : sizes){
		cout << f.smiddle() << endl;
		cout << f.startTime() << endl;
		cout << f.middle() << endl;
		cout << ps.set(i) << endl;
		cout << f.middle() << endl;
		cout << f.endTime() << endl;
		cout << f.smiddle() << endl;
	}
	cout << f.bottom() << endl;
	
	return 0;

}