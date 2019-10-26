
// C++ for C Coders & Data Structures
// Lecture note by idebtor@gmail.com
//
// Lab 1:
//  - C and C++ coding using g++
//  - a new line escape character and endl manipulator
//  - `using namespace std;`
//  - Understanding `int main(int argc, char *argv[])`
//  - Using functions and prototype
//  - Compiling multiple source files
//
// The following command line compiles a source files and builds
// an executable a.exe or with a given name. Modify it as you need
// 		g++ hello.cpp
//		./a
//		g++ hello.cpp -o hello
//		./hello

#include <iostream>
using namespace std;
// write c code that prints "Hello World!" twice, one per line.

int main(int argc, char *argv[]) {
	// your code here
  cout << "argv[0] = " << argv[0] << endl;

  if(argv[1]!=0){
    for (int i = 1; i < argc; ++i)
      cout << "Hello " << argv[i] << endl;
    }
  else
      cout << "Hello World!" << endl;

  return 0;
}
