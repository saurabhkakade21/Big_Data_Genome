//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 05
//Large Scale Data Structures

//header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "homework.h" //part A
#include <time.h>

using namespace std;
	
int main(int argc, char ** argv){ 

////////////////////////////////////////////////////////////////////////////////////	
//Lets do sanity checks to make sure the proper number of parameters were passed in
////////////////////////////////////////////////////////////////////////////////////

	if (argc != 5)
	{  // unexpected program call
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: Total 4 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <filepath01> <size> <number> <error>" << endl;
		cout << "Example:" << endl;
		cout << "./homework A file1.fa 36 100 5"  << endl;
		cout << "=========================="<< endl << endl;
		cout << "exiting..." << endl;
		exit(-1);
	}
	else
	{
		cout << "\n\nThe number of arguments passed: " << argc << endl;
		cout << "The Main file is: "  << argv[0] << endl; 	//main file exe
		cout << "The special flag is: " << argv[1] << endl; 	//selection of options
		cout << "The SARS-COV2 Genome file is: "  << argv[2] << endl;	//file path 01
		cout << "The user random size is: "  << argv[3] << endl;	//number
		cout << "The user error percent is (0 or 5): "  << argv[4] << endl;	//number
	}

	time_t begin, end; // timer initialization
	
	char* second_argument = argv[1];	//switch case parameter

	int user_input_for_no_of_reads = atoi(argv[3]);

	int user_input_for_no_of_error_percent = atoi(argv[4]);

	prefix_trie fasta;		//calling class from homework.h to solve part 01
	prefix_trie fasta01(fasta);	

		
	time(&begin);	//to begin the timer

	switch(*second_argument)
	{
		
		//Part 01 - A
		case 'A': 
			cout << "\nProblem 01 - Part A: \n" << endl;
			fasta.Random_Fragments(argv[2],user_input_for_no_of_reads,user_input_for_no_of_error_percent);

			fasta.Search_Trie(argv[2]);
			
			break;

		//Part 01 - B
		case 'B': 
			cout << "\nProblem 01 - Part B: \n" << endl;
			fasta.Random_Fragments(argv[2],user_input_for_no_of_reads,user_input_for_no_of_error_percent);

			fasta.Search_Trie(argv[2]);	
			break;

		
		default:
			
			cout << "Enter special flag argument as A or B !!!" << endl;
			
			break;
	}

    time(&end);	//to end the timer
    time_t elapsed = end - begin;
    printf("Time measured: %ld seconds.\n", elapsed);
	return (0);
}
