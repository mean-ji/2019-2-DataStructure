/*
On my honour, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
Signed: MinjiKim Section: 01 Student Number: 21600069
* Lecture Note by idebtor@gmail.com
*
* This program is written to run the sort algorithms.
* It takes the number of data samples to sort from the user.
* Then, the int array is created and filled with random numbers.
* User may selection one of sort functions to be used. Then
* execution time and its output is displayed.
*
* History:
* 02/10/19:		Created in C++
*
* Before Compilation, you must have some files (static library and
* include file) ready as shown below:
*   include/nowic.h
*		include/sort.h
*		lib/libnowic.a        (nowic.lib for Visual Studio)
* 	lib/sort.a            (sort.lib for Visual Studio)
* Compilation:
*	g++ selection.cpp insertion.cpp quicksort.cpp bubble.cpp
*       sortDriver.cpp -I../include -L../lib -lnowic -lsort -o sort
*/

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include "nowic.h"
#include "sort.h"
#define STARTING_SAMPLES 500
using namespace std;

void printList(int *list, int n, int max_print, int per_line);

void randomize(int list[], int size);
void profiling(void (*sortFunc)(int*, int), int* list, int n, bool random=true);

// sortDriver to test sort functions or algorithms.
int main(int argc, char *argv[]) {
	void (*comp)(int[],int)=selectionSort;
	int count=0;
	int N = 0;						// default sample size
	int keyin;
	int *list = nullptr;				// input and output buffer
	int max_print = 10;				// default max_print(=front_part+last_part)
	int per_line = max_print / 2;	// default samples per line to print
	clock_t start;
	char randomized = 'N';
	char option_char;
	char option_str[512];
	char algorithm_list[4][20] = {"Bubble", "Insertion", "Quicksort", "Selection"};
	enum algorithm_enum { BUBBLE, INSERTION, QUICKSORT, SELECTION };
	int  algorithm_chosen = SELECTION;  // default algorithm chosen
	DPRINT(cout << ">main...N=" << N << endl;)

	// Use setvbuf() to prevent the output from buffered on console.
	setvbuf(stdout, NULL, _IONBF, 0);

	do {
		sprintf(option_str, "[sort=%s N=%d randomized=%c max_print=%d per_line=%d]",
			algorithm_list[algorithm_chosen], N, randomized, max_print, per_line);
		cout << "\n\tOPTIONS: " << option_str << "\n"
			"\tn - number of samples size and initialize\n"
			"\tr - randomize(shuffle) samples\n"
			"\tv - reverse ordered[toggle]\n"
			"\ta - algorithm to run\n"
			"\ts - sort()\n"
			"\tp - profiling\n"
			"\tm - max samples to display at front or rear\n"
			"\td - max samples to display per line\n";

		option_char = GetChar("\tCommand(q to quit): ");
		DPRINT(cout << "option_char = " << option_char << endl;);

		switch (option_char) {
		case 'a': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			switch (GetChar("\tEnter b for bubble, i for insertion, s for selection, q for quick sort: ")) {
			case 'b': algorithm_chosen = BUBBLE; comp = bubbleSort;		break;
			case 'i': algorithm_chosen = INSERTION; comp = insertionSort;	break;
			case 'q': algorithm_chosen = QUICKSORT; comp = quickSort;	break;
			case 's': algorithm_chosen = SELECTION; comp = selectionSort;	break;
			default: { cout << "\tNo such an algorithm available. Try it again.\n"; break; } }

			//////////////
			break;

		case 'n': DPRINT(cout << "case = " << option_char;);
			keyin = GetInt("\tEnter input sample size: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}

			// set N with the new keyin value
			// before allocating the new list, free the old list if not nullptr
			// allocate memory for new data samples
			// Fill the list with numbers from 0 to n - 1.
			// your code here
			N = keyin;
			if (list != nullptr) delete[] list;
			list = new (nothrow) int[N];
			assert(list != nullptr);
			for (int i = 0; i < N; i++) list[i] = i;

			printList(list, N, max_print, per_line);
			///////////////////////
			break;

		case 'r': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 1) {
				cout << "\tSet sample size first or larger\n";
				break;
			}
			randomize(list, N);
			randomized = 'Y';

			printList(list, N, max_print, per_line);
			break;

		case 'v': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 0) {
				cout << "\tSet sample size first\n";
				break;
			}

			if(count%2==1){
				for (int i = 0; i < N; i++) list[i] = i;
			}else{
				int j = N - 1;
				for (int i = 0; i < N; i++) list[i] = j--;
			}
			count++;
			randomized = 'N';
			printList(list, N, max_print, per_line);
			break;
		case 'p':
			if(N < STARTING_SAMPLES){
				cout << "Enter a number much larger than 500.";
				return EXIT_FAILURE;
			}
			profiling(comp, list, N, false);

			break;
		case 's': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 0) {
				cout << "\tSet sample size first\n";
				break;
			}
			cout << "\tThe clock ticks and " << algorithm_list[algorithm_chosen] << " begins...\n";
			start = clock();

			//cout << "your one-line code here: use a function pointer" << endl;

			comp(list,N);

			printList(list, N, max_print, per_line);
			randomized = 'N';
			//////////////////
			cout << endl;
			cout << "\tDuration: " << (clock() - start)/(double)CLOCKS_PER_SEC << " seconds\n";
			break;

		case 'm': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			keyin = GetInt("\tEnter max sample size to display: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}
			max_print = keyin;
			printList(list, N, max_print, per_line);

			////////////////
			break;
		case 'd': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			keyin = GetInt("\tEnter max sample per line to display: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}
			per_line = keyin;
			printList(list, N, max_print, per_line);

			////////////////
			break;
		default:
			break;
		}
	} while (option_char != 'q');

	if (list != nullptr) delete[] list;
	// system("pause");
	DPRINT(cout << ">main" << endl;)
	return EXIT_SUCCESS;
}
