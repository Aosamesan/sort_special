#include"sort.h"

using namespace Painter;
using namespace Sorts;

int main(){
	cout << "Press Any Key to Start... ";
	getchar();

	FramePainter f;
	PrintSorter ps;
	unsigned int sizes[] = { 100, 500, 1000, 5000, 10000, 15000 };
	
	cout << f.top() << endl;
	cout << f.startTime() << endl;
	cout << f.smiddle() << endl;
	cout << f.header() << endl;
	for (unsigned int i : sizes){
		cout << f.smiddle() << endl;
		cout << ps.set(i) << endl;
	}
	cout << f.smiddle() << endl;
	cout << f.endTime() << endl;
	cout << f.bottom() << endl;

	return 0;

}