//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures

//header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "homework.h"
#include <time.h>

using namespace std;

int user_defined_values = 1;	//size of random read sequence 
	
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

	char* second_argument = argv[1];	//switch case parameter

	FASTAreadset_DA fasta(argv[2]);	// calling class from homework.h to solve part 01

	
	time_t begin, end;

	time(&begin);


	switch(*second_argument)
	{
		
		//Part 01
		case 'A': 
			cout << "\nFunction in C++ that implements the Smith-Waterman alignment between two genomic sequences.: \n" << endl;
			fasta.read_reads();
			// fasta.display_reads();
			fasta.read_genomic_data(argv[3]);
			// fasta.print_genomic_data();
			fasta.SW_algorithm();
			break;

		case 'B': 
			cout << "\nGenerate 1K, 10K, 100K, and 1M (million) completely random genomic sequences (50nt) to use as targets for alignment and use SARS-COV2 genome as subject. Perform alignment of the queries to the subject sequence and record time to completion (in seconds / minutes).: \n" << endl;
			
			fasta.random_seq_generator(user_defined_values);
			// fasta.display_reads();
			fasta.read_genomic_data(argv[3]);
			fasta.SW_algorithm();
			
			break;

		//Part 02
		case 'C': 
			cout << "\nAssessing the impact of the hash table size: \n" << endl;
			// fasta_chain.read_reads_chain();
			// fasta_chain.hash_table_creation();
			// fasta_chain.display_hash_collisions();
			// fasta_chain.display_reads_chain();
			break;

		case 'D': 
			cout << "\nSearching in the chain-linked hash table: \n" << endl;
			// fasta_chain.read_reads_chain();
			// fasta_chain.hash_table_creation();
			// fasta_chain.display_hash_collisions();
			// fasta_chain.display_reads_chain();
			// fasta_chain.read_genomic_data_chain(argv[3]);
			// fasta_chain.search_genomic_data_chain();
			break;


		default:
			cout << "Enter second argument from A to D !!!" << endl;
			break;
	}
	time(&end);
    time_t elapsed = end - begin;
	printf("Time measured: %ld minutes.\n", elapsed/60);
	
	return (0);
}
