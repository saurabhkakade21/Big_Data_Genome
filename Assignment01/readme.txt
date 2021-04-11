My program is of 2 modules
	1.FASTAread.cpp , which is main file
	2.fastaread.h, which is header file that exhibits class functionalities.
I used make to compile my program
To run my program I used 
	srun ./a.out example.fa 36000000
	my code take filepath and number of lines as Commandline argument.
	example.fa is file that contains data.
	36000000 is the number of lines to be read.
	
After compiling my code it goes to SWITCH operation in my program which is as follows and asks to select an operation to be performed
"SELECT AN OPERATION" 
"A. Initialize (fill up) the array data-structure with the 1 million reads."
"B. Initialize (fill up) the array data-structure with the entire 36 million reads."
"C. Compute Statistics(Unique seq frag, No of Reads, Char count of A,C,G,T)" 
"D. Deallocate the array"
"E. Sort 36 Million data "

After choosing any of the above operations it performs the following functions:

In case A- Initilizing of 1 Million reads is done.
In case B- Initilizing of 36 Million reads is done.
In case C- It computes the following statistics.
		1.Unique Sequence Fragments in the given Dataset after reading.
		2.Number of reads in the given dataset after reading.
		3.Character count of A,C,G,T.
In case D- The initialized array is deallocated.
In case E- The given dataset is sorted using Mergesort.

Then the program is terminated after performing any of the above operations. 
