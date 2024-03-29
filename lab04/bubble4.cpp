// bubble sort by idebtor@gmail.com
// This brute force version of bubble sort that takes O(n^2).
// 2019/02/02: Created
//
// Compilation:
// g++ bubble.cpp -o sort
// g++ bubble.cpp -o sort -DDEBUG
// To use DEBUG or test it, compile with -D option and turn #if 1 on.
// To make the function included in other program, turn #if 0 off.

#include <iostream>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif
bool less(int x, int y) {   return x < y;   }   // use this for ascending
bool more(int x, int y) {   return x > y;   }
void bubbleSort(int *list, int n, bool (*comp)(int, int)) {
	DPRINT(cout << "BUBBLE SORTING...\n");
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) // last i elements are already in place
			if (comp(list[j + 1], list[j]))
				swap(list[j], list[j + 1]);
		DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl);
	}
}

#if 1
void printList(int *list, int n) {
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;
}

int main() {
	int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	int N = sizeof(list) / sizeof(list[0]);

	cout << "UNSORTED: " << endl;
	printList(list, N);
	bool (*comp)(int, int) = ::less;
	bubbleSort(list, N, ::less);    // ascending
	cout << "BUBBLE SORTED: " << endl;
	printList(list, N);
  comp=more;
  bubbleSort(list, N, more);      // descending

	cout << "BUBBLE SORTED: " << endl;
	printList(list, N);
}
#endif
