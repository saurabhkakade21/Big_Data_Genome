//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 04
//Large Scale Data Structures

//header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "homework.h" //part A
#include "homework_BLAST.h" //part B
#include <time.h>

using namespace std;
	
int main(int argc, char ** argv){ 

////////////////////////////////////////////////////////////////////////////////////	
//Lets do sanity checks to make sure the proper number of parameters were passed in
////////////////////////////////////////////////////////////////////////////////////

	if (argc != 4){  // unexpected program call
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: Total 4 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <filepath01> <filepath02>" << endl;
		cout << "Example:" << endl;
		cout << "./homework A file1.fa file2.fa"  << endl;
		cout << "=========================="<< endl << endl;
		cout << "exiting..." << endl;
		exit(-1);
	}else{

		cout << "\n\nThe number of arguments passed: " << argc << endl;
		cout << "The first argument is: " << argv[0] << endl; 	//main file exe
		cout << "The second argument is: " << argv[1] << endl; 	//selection of options
		cout << "The third argument is: " << argv[2] << endl;	//file path 01
		cout << "The fourth argument is: " << argv[3] << endl;	//file path 02
	}

	int user_defined_values = 1000000;	//size of random read sequence 

	time_t begin, end; // timer initialization
	
	char* second_argument = argv[1];	//switch case parameter

	FASTAreadset_DA fasta(argv[2]);		//calling class from homework.h to solve part 01
	FASTAreadset_BLAST fasta_BLAST(argv[2]); //calling class from homework_BLAST.h to solve part 02
		
	time(&begin);	//to begin the timer

	switch(*second_argument)
	{
		
		//Part 01 - A
		case 'A': 
			cout << "\nFunction in C++ that implements the Smith-Waterman alignment between two genomic sequences.: \n" << endl;
			fasta.read_queries();
			// fasta.display_read_queries();
			fasta.read_genomic_data(argv[3]);
			// fasta.print_genomic_data();
			fasta.SW_algorithm();
			break;

		//Part 01 - B
		case 'B': 
			cout << "\nGenerate 1K, 10K, 100K, and 1M (million) completely random genomic sequences (50nt) to use as targets for alignment and use SARS-COV2 genome as subject. Perform alignment of the queries to the subject sequence and record time to completion (in seconds / minutes).: \n" << endl;
			
			fasta.random_seq_generator(user_defined_values); // define the user defined values from this main program
			// fasta.display_random_queries(); //display random genomic sequences
			fasta.read_genomic_data(argv[3]);
			// fasta.print_genomic_data();
			fasta.SW_algorithm();
			
			break;

		//Part 02 - A
		case 'C': 
			cout << "\n:Having a BLAST - Implement a seed-based Smith Waterman: \n" << endl;
		
			fasta_BLAST.read_queries_11mers();
            //fasta_BLAST.display_read_queries_blast();
			fasta_BLAST.read_genome_11mers(argv[3]);
            //fasta_BLAST.print_genomic_data_BLAST();
			fasta_BLAST.hash_table_creation(argv[3]);
			fasta_BLAST.search_query_seed_in_hashtable(argv[3]);
			
			break;
			
        //Part 02 - B
		case 'D': 
			cout << "\nTest your code on a set of 1K, 10K, 100K, and 1M (million) completely random 50-mers, aligning them to SARS-COV2 genome. How long did it take? Compare it to the results in problem 1B. : \n" << endl;
			fasta_BLAST.random_seq_generator(user_defined_values);
			fasta_BLAST.read_genome_11mers(argv[3]);
			fasta_BLAST.hash_table_creation(argv[3]);
			fasta_BLAST.search_random_query_seed_in_hashtable(argv[3]);
			break;

		default:
			cout << "Enter second argument from A to D !!!" << endl;
			break;
	}

    time(&end);	//to end the timer
    time_t elapsed = end - begin;
    printf("Time measured: %ld minutes.\n", elapsed/60);

	return (0);
}
