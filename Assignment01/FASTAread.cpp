#include "fastaread.h"

int main(int argc,char* argv[]){
string filepath=argv[1];
int no_lines=atoi(argv[2]);
FASTAread fr(filepath);
char X;
cout << "SELECT AN OPERATION" << endl;
cout << "A. Initialize (fill up) the array data-structure with the 1 million reads." << endl;
cout << "B. Initialize (fill up) the array data-structure with the entire 36 million reads." << endl;
cout << "C. Compute Statistics(Unique seq frag, No of Reads, Char count of A,C,G,T)" << endl;
cout << "D. Deallocate the array" << endl;
cout << "E. Sort 36 Million data " << endl;
cin >> X;
switch(X){
case 'A': cout << "Initializing array for 1 million" << endl;
fr.read(no_lines);
break;
case 'B': cout << "Initializing array for 36 million" << endl;
fr.read(no_lines);
break;
case 'C': cout << "Compute Statistics" << endl;
fr.read(no_lines);
fr.compute_statistics();
break;
case 'D': cout << "Deallocate Array" << endl;
fr.read(no_lines);
fr.delete_my_array();
break;
case 'E': cout << "Sort 36 Million data" << endl;
fr.read(no_lines);
fr.sort_data();
break;
default : cout << "Choose A,B,C,D or E"  << endl;
break;
}
}

