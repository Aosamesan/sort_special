#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>
#include<ctime>
#include<chrono>
#include<cstdlib>
#include<cstring>
#include"bst.h"
#define BIGNUMBER 40000
#define UNABLEQUAD 30000
using namespace std;

namespace Painter{

	class FramePainter{
	public:
		FramePainter(){
			focus = Focus::NONE;
		}

		friend ostream& operator<<(ostream& os, FramePainter& fp);

		FramePainter& top(){
			focus = Focus::TOP;
			return *this;
		}

		FramePainter& middle(){
			focus = Focus::MIDDLE;
			return *this;
		}

		FramePainter& smiddle(){
			focus = Focus::SMIDDLE;
			return *this;
		}

		FramePainter& bottom(){
			focus = Focus::BOTTOM;
			return *this;
		}

		FramePainter& header(){
			focus = Focus::HEADER;
			return *this;
		}

		FramePainter& startTime(){
			focus = Focus::STARTTIME;
			return *this;
		}

		FramePainter& endTime(){
			focus = Focus::ENDTIME;
			return *this;
		}

	private:
		enum Focus{
			NONE = -1,
			TOP = 0,
			MIDDLE = 1,
			SMIDDLE = 2,
			BOTTOM = 3,
			HEADER = 4,
			STARTTIME = 5,
			ENDTIME = 6
		};

		Focus focus;
	};

	ostream& operator<<(ostream& os, FramePainter& fp){
		if (fp.focus == FramePainter::Focus::TOP
				|| fp.focus == FramePainter::Focus::MIDDLE
				|| fp.focus == FramePainter::Focus::SMIDDLE
				|| fp.focus == FramePainter::Focus::BOTTOM
				){
			if (fp.focus == FramePainter::Focus::TOP)
				os << "┌";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "├";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "┝";
			else
				os << "└";

			for (int i = 0; i < 20; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "─";
				else
					os << "━";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "┬";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "┼";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "┿";
			else
				os << "┴";

			for (int i = 0; i < 30; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "─";
				else
					os << "━";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "┬";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "┼";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "┿";
			else
				os << "┴";

			for (int i = 0; i < 20; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "─";
				else
					os << "━";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "┐";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "┤";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "┥";
			else
				os << "┘";
		}
		else if (fp.focus == FramePainter::Focus::HEADER){
			os << "│" << setw(20) << left << "Sort Name" << "│" <<
				setw(30) << left << "Time Interval" << "│" <<
				setw(20) << left << "Size" << "│";
		}
		else if (fp.focus == FramePainter::Focus::STARTTIME){
			time_t startTime = time(NULL);
			tm * start = localtime(&startTime);
			char str[30] = { 0, };
			sprintf(str, " Start : %02d:%02d:%02d", start->tm_hour, start->tm_min, start->tm_sec);

			os << "│" << setw(20) << left << "" << "│" <<
				setw(30) << left << str << "│" <<
				setw(20) << left << "" << "│";

		}
		else if (fp.focus == FramePainter::Focus::ENDTIME){
			time_t endTime = time(NULL);
			tm * end = localtime(&endTime);
			char str[30] = { 0, };
			sprintf(str, " End   : %02d:%02d:%02d", end->tm_hour, end->tm_min, end->tm_sec);

			os << "│" << setw(20) << left << "" << "│" <<
				setw(30) << left << str << "│" <<
				setw(20) << left << "" << "│";
		}

		return os;
	}
}

namespace UnsortedList{
	unsigned int GetPrime(unsigned int srcSize){
		vector<int> primes;
		unsigned int halfSize = srcSize / 2;
		primes.push_back(2);

		for (unsigned int i = 3; i <= halfSize; i++){
			bool isPrime = true;

			for (unsigned int p : primes){
				if (i % p == 0){
					isPrime = false;
					break;
				}
			}

			if (isPrime)
				primes.push_back(i);
		}

		return primes.back();
	}

	vector<int> MakeList(unsigned int srcSize){
		const unsigned int BIG_PRIME = GetPrime(srcSize);
		bool * check = new bool[srcSize];
		vector<int> arr;
		int tmp;

		if (srcSize <= BIGNUMBER){
			for (unsigned int i = 0; i < srcSize; i++)
				check[i] = false;

			srand((unsigned int)time(NULL));
			for (unsigned int i = 0; i < srcSize;){
				tmp = rand() % srcSize;
				if (check[tmp] == false){
					check[tmp] = true;
					arr.push_back(tmp);
					i++;
				}
			}
		}
		else {
			for (unsigned int i = 0; i < srcSize; i++){
				arr.push_back(rand() % srcSize);
			}
		}

		delete[] check;
		return arr;
	}

	bool VectorCollisionTest(vector<int>& vec, unsigned int srcSize){
		if (vec.size() <= BIGNUMBER){
			bool * check = new bool[srcSize];
			for (unsigned int i = 0; i < srcSize; i++)
				check[i] = false;

			for (unsigned int i = 0; i < srcSize; i++){
				if (!check[vec[i]])
					check[vec[i]] = true;
				else
					return false;
			}

			delete[] check;
		}
		return true;
	}
}

namespace Sorts{
	using namespace UnsortedList;
	using namespace Painter;

	const char* SORT_NAMES[] = {
		"Bubble Sort",
		"Selection Sort",
		"Insertion Sort",
		"Sorting by BST",
		"Quick Sort",
		"Merge Sort"
	};

	const unsigned short BUBBLE_SORT = 0;
	const unsigned short SELECTION_SORT = 1;
	const unsigned short INSERTION_SORT = 2;
	const unsigned short SORT_BY_BST = 3;
	const unsigned short QUICK_SORT = 4;
	const unsigned short MERGE_SORT = 5;

	const unsigned int NUM_OF_SORTS = 6;


	auto isSorted = [](vector<int>& vec) -> bool {
		int size = vec.size();
		for (int i = 0; i < size - 1; i++){
			if (vec[i] > vec[i + 1])
				return false;
		}

		return true;
	};

	auto bubbleSort = [](vector<int> vec, int size) -> bool{
		for (int i = size - 1; i > 0; i--)
			for (int j = 0; j < i; j++){
				if (vec[j] > vec[j + 1]){
					int tmp = vec[j];
					vec[j] = vec[j + 1];
					vec[j + 1] = tmp;
				}
			}

		return isSorted(vec);
	};

	auto selectionSort = [](vector<int> vec, int size)-> bool{
		int minIdx;

		for (int i = 0; i < size - 1; i++){
			minIdx = i;
			for (int j = i + 1; j < size; j++){
				if (vec[j] < vec[minIdx]){
					minIdx = j;
				}
			}
			int tmp = vec[minIdx];
			vec[minIdx] = vec[i];
			vec[i] = tmp;
		}

		return isSorted(vec);
	};

	auto insertionSort = [](vector<int> vec, int size)-> bool{
		int rem;
		int j;

		for (int i = 1; i < size; i++){
			rem = vec[j = i];
			while (--j >= 0 && rem < vec[j]){
				vec[j + 1] = vec[j];
			}
			vec[j + 1] = rem;
		}

		return isSorted(vec);
	};


	void quickSortRecursive(vector<int>& vec, int left, int right){
		if (left == right)
			return;
		int pivot, lHold, rHold;

		lHold = left;
		rHold = right;
		pivot = vec[left];

		while (left < right){
			while ((vec[right] >= pivot) && (left < right))
				right--;
			if (left != right){
				vec[left] = vec[right];
				left++;
			}
			while ((vec[left] <= pivot) && (left < right))
				left++;
			if (left != right){
				vec[right] = vec[left];
				right--;
			}
		}

		vec[left] = pivot;
		pivot = left;
		left = lHold;
		right = rHold;

		if (left < pivot)
			quickSortRecursive(vec, left, pivot - 1);
		if (right > pivot)
			quickSortRecursive(vec, pivot + 1, right);
	}

	auto quickSort = [](vector<int> vec, int size)-> bool{
		quickSortRecursive(vec, 0, size - 1);

		return isSorted(vec);
	};

	auto BSTSort = [](vector<int> vec, int size)-> bool{
		BSTree<int> tree;
		auto push = [&vec](int n){
			vec.push_back(n);
		};

		for (int i : vec){
			tree.Insert(i);
		}
		vec.clear();
		
		tree.BSTSort(push);

		return isSorted(vec);
	};

	void merge(vector<int>& vec, int left, int right){
		int mid = (left + right) / 2;

		vector<int> tVec;

		int i = left;
		int j = mid;
		int input;
		
		while(i < mid && j < right){
			input = (vec[i] < vec[j]) ? vec[i++] : vec[j++];
			tVec.push_back(input);
		}

		while(i < mid)
			tVec.push_back(vec[i++]);
		while(j < right)
			tVec.push_back(vec[j++]);

		for(i = 0; i < tVec.size(); i++){
			vec[i + left] = tVec[i];
		}
	}

	void mergeSortRecursive(vector<int>& vec, int left, int right){
		try{
			if(right - left < 2)
				return;
			if(left < right){
				int mid = (left + right) / 2 ;

				mergeSortRecursive(vec, left, mid);
				mergeSortRecursive(vec, mid, right);

				merge(vec, left, right);
			}
		} catch(exception e){
			for(auto i : vec)
				cout << i << ", ";
			cout << endl;
		}
	}

	auto mergeSort = [](vector<int> vec, int size) -> bool{
		mergeSortRecursive(vec, 0, size);

		merge(vec, 0, size);

		return isSorted(vec);
	};

	template<typename T>
	long long Sorter(vector<int>& vec, T sortFunc){
		int size = vec.size();
		long long lap = 125;
		chrono::system_clock::time_point start;
		chrono::system_clock::time_point end;
		
		if (VectorCollisionTest(vec, size)){
			start = chrono::high_resolution_clock::now();
			auto sortedState = sortFunc(vec, size);
			end = chrono::high_resolution_clock::now();
			
			lap = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

			if (!sortedState){
				cout << "Not Sorted" << endl;
				return -1;
			}
		}
		else {
			cout << "Vector Collided!" << endl;
			return -1;
		}

		return lap;
	}

	class PrintSorter{
	public:
		PrintSorter(){
			size = 0;
			arr.clear();
		}

		PrintSorter& set(unsigned int size){
			this->size = size;
			arr = MakeList(this->size);

			return *this;
		}

		friend ostream& operator<<(ostream&, PrintSorter&);

	private:
		vector<int> arr;
		unsigned int size;
	};

	ostream& operator<<(ostream& os, PrintSorter& ps){
		if (ps.size > 0){
			long long lap;

			for (int i = 0; i < NUM_OF_SORTS; i++){
				if (((i == BUBBLE_SORT || i == SELECTION_SORT || i == INSERTION_SORT) && ps.size <= UNABLEQUAD)
					|| (i == SORT_BY_BST || i == QUICK_SORT || i == MERGE_SORT)){
					switch (i){
					case BUBBLE_SORT:
						lap = Sorter(ps.arr, bubbleSort);
						break;
					case SELECTION_SORT:
						lap = Sorter(ps.arr, selectionSort);
						break;
					case INSERTION_SORT:
						lap = Sorter(ps.arr, insertionSort);
						break;
					case QUICK_SORT:
						lap = Sorter(ps.arr, quickSort);
						break;
					case SORT_BY_BST:
						lap = Sorter(ps.arr, BSTSort);
						break;
					case MERGE_SORT:
						lap = Sorter(ps.arr, mergeSort);
						break;
					}

					os << "│" << setw(20) << left <<SORT_NAMES[i] << "│" <<
						right << setw(8) << (lap / 1000000000) % 1000 << "s " << setw(3) << (lap / 1000000) % 1000 << "ms " <<
						setw(3) << (lap / 1000) % 1000 << "mis " <<
						setw(3) << lap % 1000 << "ns" << setw(5) << "│" << setw(20) << ps.size << "│";
					if (i != NUM_OF_SORTS - 1)
						os << endl;
				}
			}
		}

		return os;
	}
}
