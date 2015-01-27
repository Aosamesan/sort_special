#include"sort.h"

using namespace Painter;
using namespace Sorts;

int main(int argc, char** argv){
	FramePainter f;
	PrintSorter ps;
	unsigned int numOfTests;
	unsigned int tmpSize;
	vector<unsigned int> sizes;
	
	if(argc == 1) {
		try{
			cin >> numOfTests;
			for(unsigned int i = 0; i < numOfTests; i++){
				cin >> tmpSize;
				if(tmpSize == 0)
					throw new exception();
				sizes.push_back(tmpSize);
			}
		} catch(exception e){
			cout << e.what() << endl;
			return -2;
		}
	} else {
		cerr << "Usage 1 : " << argv[0] << endl;
		cerr << "Usage 2(Redirection) : " << argv[0] << " < file" << endl;
		return -1;
	}

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
