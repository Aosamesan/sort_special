#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>
#include<ctime>
#include<chrono>
#include<cstdlib>
#include<string>
#define BIGNUMBER 30000
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
				os << "��";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "��";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "��";
			else
				os << "��";

			for (int i = 0; i < 10; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "��";
				else
					os << "��";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "��";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "��";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "��";
			else
				os << "��";

			for (int i = 0; i < 15; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "��";
				else
					os << "��";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "��";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "��";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "��";
			else
				os << "��";

			for (int i = 0; i < 10; i++)
				if (fp.focus != FramePainter::Focus::SMIDDLE)
					os << "��";
				else
					os << "��";

			if (fp.focus == FramePainter::Focus::TOP)
				os << "��";
			else if (fp.focus == FramePainter::Focus::MIDDLE)
				os << "��";
			else if (fp.focus == FramePainter::Focus::SMIDDLE)
				os << "��";
			else
				os << "��";
		}
		else if (fp.focus == FramePainter::Focus::HEADER){
			os << "��" << setw(20) << left << "Sort Name" << "��" <<
				setw(30) << left << "Time Interval" << "��" <<
				setw(20) << left << "Size" << "��";
		}
		else if (fp.focus == FramePainter::Focus::STARTTIME){
			time_t startTime = time(NULL);
			tm start;
			localtime_s(&start, &startTime);
			char str[17] = { 0, };
			sprintf_s(str, "\tStart : %d:%d:%d", start.tm_hour, start.tm_min, start.tm_sec, 17);

			os << "��" << setw(20) << left << "" << "��" <<
				setw(23) << left << str << "��" <<
				setw(20) << left << "" << "��";

		}
		else if (fp.focus == FramePainter::Focus::ENDTIME){
			time_t endTime = time(NULL);
			tm end;
			localtime_s(&end, &endTime);
			char str[17] = { 0, };
			sprintf_s(str, "\tEnd   : %d:%d:%d", end.tm_hour, end.tm_min, end.tm_sec, 17);

			os << "��" << setw(20) << left << "" << "��" <<
				setw(23) << left << str << "��" <<
				setw(20) << left << "" << "��";

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

	auto isSorted = [](vector<int>& vec) -> bool {
		int size = vec.size();
		for (int i = 0; i < size - 1; i++){
			if (vec[i] > vec[i + 1])
				return false;
		}

		return true;
	};

	auto bubbleSort = [](vector<int> vec, int size){
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

	auto selectionSort = [](vector<int> vec, int size){
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

	auto insertionSort = [](vector<int> vec, int size){
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

	auto quickSort = [](vector<int> vec, int size){
		quickSortRecursive(vec, 0, size - 1);

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
			long long laps[4] = { Sorter(ps.arr, bubbleSort),
				Sorter(ps.arr, selectionSort),
				Sorter(ps.arr, insertionSort),
				Sorter(ps.arr, quickSort) };
			const char* sorts[4] = { "Bubble Sort", "Selection Sort", "Insertion Sort", "Quick Sort" };

			for (int i = 0; i < 4; i++){
				os << "��" << setw(20) << left << sorts[i] << "��" <<
					right << setw(8) << (laps[i] / 1000000000) % 1000 << "s " << setw(3) << (laps[i] / 1000000) % 1000 << "ms " <<
					setw(3) << (laps[i] / 1000) % 1000 << "mis " <<
					setw(3) << laps[i] % 1000 << "ns" << setw(4) << "��" << setw(20) << ps.size << "��";
				if (i != 3)
					os << endl;
			}
		}

		return os;
	}
}